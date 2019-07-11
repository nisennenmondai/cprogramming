#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include <linux/can/raw.h>

#define CANFD_DLEN 64


static void *can_read_fd(void *arg);
static void *can_write_fd(void *arg);
