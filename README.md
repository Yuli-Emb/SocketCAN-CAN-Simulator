# SocketCAN-CAN-Simulator - TEMPORARY NOTES // TO-DO - EDIT 

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