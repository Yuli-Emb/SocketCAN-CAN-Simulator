#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int s, nbytes;
struct sockaddr_can addr;
struct ifreq ifr;
struct can_frame frame;

struct can_frame test_frame = {
    .can_id = 0x123,
    .len = 4,
    .data = {0xDE, 0xAD, 0xBE, 0xEF}
};

/*  CAN frame structure
struct can_frame {
    canid_t can_id;     // 32 bit CAN ID and EFF/RTR/ERR flags
                        // EFF - Extended Frame Format. Set when frame uses 29-bit
                        // identifier instead of standard 11-bit
                        // RTR - Remote Transmission Request. Set when the frame is
                        // remote. Frame requests data from another node instead of
                        // carrying data itself.
                        // ERR - Error Frame. Set when frame represents an error 
                        // reported by CAN controller/driver rather than real bus frame

    __u8 len;           // Contains the payload length in bytes
    __u8 __pad;         // Padding
    __u8 __res0;        // Reserved padding
    __u8 len8_dlc;      // Optional DLC for 8 byte payload length

    __u8 data[8] __attribute__((aligned(8)));
                        // Forces the compiler to align this field to an 8-byte boundary
                        // in memory. To be short - no matter where this struct is
                        // allocated (stack, heap, etc.) the payload bytes will start on
                        // an address divisible by 8
};*/

/* Tells bind() which CAN interface to attach this socket to
struct sockaddr_can {
    sa_family_t can_family;
    int can_ifindex;
};*/

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

    nbytes = write(s, &test_frame, sizeof(struct can_frame)); // Writing CAN frame

    check_ERROR(nbytes, "read"); 
}