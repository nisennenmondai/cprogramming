#include "protoisotp.h"

static void init_data(uint8_t *data, int *size) 
{
    for (int i = 0; i < *size; i++) {
        data[i] = i;
    }
}

static void *send_isotp(void *arg) 
{
    (void)arg;
    int ret = 0;
    int size = DATASIZE;
    uint8_t data[size];
    init_data(data, &size);

    socket_fd_s = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP);
    if (socket_fd_s < 0) {
        perror("socket");

        return NULL;
    }

    /* bind */
    addrs.can_family = AF_CAN;
    addrs.can_ifindex = if_nametoindex("vcan0");
    addrs.can_addr.tp.tx_id = TRANS_A_ID;
    addrs.can_addr.tp.rx_id = RECV_A_ID;

    ret = bind(socket_fd_s, (struct sockaddr*) &addrs, sizeof(addrs));
    if (ret < 0) {
        perror("bind");

        return NULL;
    }

    ret = write(socket_fd_s, data, size);
    if (ret != size) {
        perror("write");

        return NULL;
    }
    return NULL;
}

static void *receive_isotp(void *size) 
{
    (void)size;
    uint64_t nbytes = 0;
    uint8_t buff[DATASIZE];

    int ret = 0;

    socket_fd_r = socket(PF_CAN, SOCK_DGRAM, CAN_ISOTP);
    if (socket_fd_r < 0) {
        perror("socket");

        return NULL;
    }

    fcopts.bs = BLOCKSIZE;    /* segment message in 8 frames max  */
    fcopts.stmin = STMIN;     /* minimum time response */
    ret = setsockopt(socket_fd_r, SOL_CAN_ISOTP, CAN_ISOTP_RECV_FC, &fcopts, sizeof(fcopts));
    if (ret < 0) {
        perror("setsockopt");

        return NULL;
    }

    /* bind */
    addrr.can_family = AF_CAN;
    addrr.can_ifindex = if_nametoindex("vcan0");
    addrr.can_addr.tp.tx_id = TRANS_B_ID;
    addrr.can_addr.tp.rx_id = RECV_B_ID;

    ret = bind(socket_fd_r, (struct sockaddr*) &addrr, sizeof(addrr));
    if (ret < 0) {
        perror("bind");

        return NULL;
    }

    nbytes = read(socket_fd_r, buff, sizeof(buff));
    if (nbytes != sizeof(buff)) {
        perror("read");

        return NULL;
    }

    /* display data */
    printf("ISO_TP frame: ");
    for (int i = 0; i < DATASIZE; i++) {
        printf("%x ", buff[i]);
    }
    printf("\n");
    return NULL;
}

int main(void)
{
    pthread_t thrd1;
    pthread_t thrd2;
    pthread_create(&thrd1, NULL, receive_isotp, NULL);
    pthread_create(&thrd2, NULL, send_isotp, NULL);
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);

    return EXIT_SUCCESS;
}
