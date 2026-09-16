#ifndef FRAME_GEN_H
#define FRAME_GEN_H

#include <string.h>
#include <linux/can.h>
struct can_frame make_frame(canid_t id, __u8 len, __u8 *data);

#endif // FRAME_GEN_H