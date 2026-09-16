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
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);              // Opening a socket
    check_ERROR(s, "socket");

    strcpy(ifr.ifr_name, "vcan0");                      // Writing string with CAN interface name in ifr_name
    check_ERROR(ioctl(s, SIOCGIFINDEX, &ifr), "ioctl"); // Asks kernel what's the index number for vcan0

    addr.can_family = AF_CAN;                           // Defines AF_CAN as family
    addr.can_ifindex = ifr.ifr_ifindex;                 // Defines received in ifr index as CAN index
    check_ERROR(bind(s, (struct sockaddr *)&addr, sizeof(addr)), "bind");    // Binds CAN interface index to socket

    /*nbytes = read(s, &frame, sizeof(struct can_frame)); // Reading frame from a socket s

    check_ERROR(nbytes, "can raw socket read");         

    printf("Received: ID = 0x%X, len = %d, data=", frame.can_id, frame.len); // Outputting data of received frame
    
    for (size_t i = 0; i < sizeof(struct can_frame); i++) { // Frame data output
        printf("%02X ", frame.data[i]);
    }

    printf("\n");*/

    __u8 data[4] = {0xDE, 0xAD, 0xBE, 0xEF};

    test_frame2 = make_frame(0x123, 4, data);

    nbytes = write(s, &test_frame2, sizeof(struct can_frame)); // Writing CAN frame

    check_ERROR(nbytes, "read"); 
}