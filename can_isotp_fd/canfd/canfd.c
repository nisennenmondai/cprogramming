/*
 * =============================================================================
 *
 *       Filename:  cantest.c
 *
 *    Description:  sample code to send and receive canfd frames
 *
 *        Version:  1.0
 *        Created:  09/19/2018 03:58:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nisennenmondai
 *   Organization:  
 *
 * =============================================================================
 */

#include "canfd.h"

static void *can_read_fd(void *arg)
{
    (void)arg;
    int fd;
    struct sockaddr_can caddr;
    struct ifreq ifr;
    const char *ifname = "vcan0";
    const int canfd_on = 1;

    if ((fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
        return NULL;
    }
    if (setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canfd_on, sizeof(canfd_on)) < 0){
        perror("setsockopt");
        return NULL;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(fd, SIOCGIFINDEX, &ifr);

    caddr.can_family  = AF_CAN;
    caddr.can_ifindex = ifr.ifr_ifindex;

    if (bind(fd, (struct sockaddr *)&caddr, sizeof(caddr)) < 0) {
        perror("bind");
        return NULL;
    }

    struct canfd_frame frame;
    int nbytes;
    memset(&frame, 0, sizeof(frame));
    nbytes = read(fd, &frame, sizeof(frame));
    if (nbytes != sizeof(frame)) {
        perror("read");
        return NULL;
    }
    printf("canfd_frame ");
    int i;
    for (i = 0; i < CANFD_DLEN; i++) {
        printf("%x ", frame.data[i]);
    }
    printf("\n");
    return NULL;
}

static void *can_write_fd(void *arg)
{
    (void)arg;
    int fd;
    int nbytes;
    struct sockaddr_can caddr;
    struct ifreq ifr;
    const char *ifname = "vcan0";
    const int canfd_on = 1;

    if ((fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
        return NULL;
    }
    if (setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &canfd_on, sizeof(canfd_on)) < 0){
        perror("setsockopt");
        return NULL;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(fd, SIOCGIFINDEX, &ifr);

    caddr.can_family  = AF_CAN;
    caddr.can_ifindex = ifr.ifr_ifindex;

    if (bind(fd, (struct sockaddr *)&caddr, sizeof(caddr)) < 0) {
        perror("bind");
        return NULL;
    }
    struct canfd_frame frame;
    frame.can_id = 0x777;
    frame.len = CANFD_DLEN;
    int i;
    for (i = 0; i < CANFD_DLEN; i++) {
        frame.data[i] = i;
    }
    nbytes = write(fd, &frame, sizeof(frame));
    if (nbytes != sizeof(frame)) {
        perror("write");
        return NULL;
    }
    return NULL;
}

int main(void)
{
    pthread_t thrd1;
    pthread_t thrd2;
    pthread_create(&thrd1, NULL, can_read_fd, NULL);
    pthread_create(&thrd2, NULL, can_write_fd, NULL);
    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);

    return EXIT_SUCCESS;
}
