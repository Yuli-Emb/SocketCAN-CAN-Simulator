#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "frame_gen.h"

int s, nbytes;
struct sockaddr_can addr;
struct ifreq ifr;
struct can_frame frame;
struct can_frame test_frame2;
struct can_frame test_frame = {
    .can_id = 0x123,
    .len = 4,
    .data = {0xDE, 0xAD, 0xBE, 0xEF}
};

// Error handling if socket isn't found
void check_ERROR(int ret, const char *err){
    if (ret < 0) {                                    
        perror(err); 
        exit(1); 
    }
}

int main(){
    srand(time(NULL) ^ getpid());
    printf("seed val: %ld\n", time(NULL));
    printf("test rand: %d\n", rand());
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);              // Opening a socket
    check_ERROR(s, "socket");

    strcpy(ifr.ifr_name, "vcan0");                      // Writing string with CAN interface name in ifr_name
    check_ERROR(ioctl(s, SIOCGIFINDEX, &ifr), "ioctl"); // Asks kernel what's the index number for vcan0

    addr.can_family = AF_CAN;                           // Defines AF_CAN as family
    addr.can_ifindex = ifr.ifr_ifindex;                 // Defines received in ifr index as CAN index
    check_ERROR(bind(s, (struct sockaddr *)&addr, sizeof(addr)), "bind");    // Binds CAN interface index to socket

    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i = 0; i < 2; i++) {
        ecu_nodes[i].last_update = start;
    }

    while(1) {
        struct timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);

        for(int i = 0; i < 2; i++) {
            long time_ms = (now.tv_sec - ecu_nodes[i].last_update.tv_sec) * 1000 + (now.tv_nsec - ecu_nodes[i].last_update.tv_nsec)/1000000;

            if(time_ms >= ecu_nodes[i].ms) {
                switch (i) {
                    case 0: engine_sim(); break;
                    case 1: wheel_control(); break;
                }
                struct can_frame f = make_frame(ecu_nodes[i].can_id, ecu_nodes[i].len, ecu_nodes[i].data);
                write(s, &f, sizeof(f));
                ecu_nodes[i].last_update = now;
            }
        }
        usleep(1000);
    }
}