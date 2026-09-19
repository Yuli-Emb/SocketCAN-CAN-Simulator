#ifndef FRAME_GEN_H
#define FRAME_GEN_H

#include <string.h>
#include <linux/can.h>
#include <stdlib.h>
#include <time.h>
#include "update.h"
#include <stdio.h>

struct can_frame make_frame(canid_t id, __u8 len, __u8 *data);
struct can_frame random_frame();
void engine_sim();
void wheel_control();

#endif // FRAME_GEN_H