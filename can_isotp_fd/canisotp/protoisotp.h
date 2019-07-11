/*
 * =============================================================================
 *
 *       Filename:  protoisotp.cpp
 *
 *    Description:  sample code to send and receive isotp frames
 *
 *        Version:  1.0
 *        Created:  09/26/2018 09:32:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  nisennenmondai
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdint.h>

#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <linux/can.h>
#include <linux/can/isotp.h>

#define DATASIZE 64

#define TRANS_A_ID   0x123
#define RECV_A_ID    0x321

#define TRANS_B_ID   0x321
#define RECV_B_ID    0x123

#define BLOCKSIZE    0x8
#define STMIN        100

static int socket_fd_s;
static int socket_fd_r;
static struct sockaddr_can addrs;
static struct sockaddr_can addrr;
static struct can_isotp_ll_options llopts;
static struct can_isotp_fc_options fcopts;
static void *receive_isotp(void *size);
static void *send_isotp(void *arg);
static void init_data(uint8_t *data, int *size);
