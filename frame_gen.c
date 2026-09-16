#include "frame_gen.h"

struct can_frame make_frame(canid_t id, __u8 len, __u8 *data) {
    struct can_frame new_frame = {
        .can_id = id,
        .len = len,
    };
    memcpy(new_frame.data, data, len);

    return new_frame;
}