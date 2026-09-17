#include "frame_gen.h"

struct can_frame random_frame(){
    srand(time(NULL));
    
    struct can_frame rand_frame = {
        .can_id = rand() % 0x800,
        .len = rand() % 9,
    };

    for (int i = 0; i < rand_frame.len; i++) {
        rand_frame.data[i] = rand() % 256;
    }

    return rand_frame;
}

struct can_frame make_frame(canid_t id, __u8 len, __u8 *data) {
    struct can_frame new_frame = {
        .can_id = id,
        .len = len,
    };
    memcpy(new_frame.data, data, len);

    return new_frame;
}

int last_update = 0;

struct can_frame engine_sim(){
    ecu_nodes[0].len = 2;

    ecu_nodes[0].data[0] = rand() % 80; // Placeholder rpm gen

    ecu_nodes[0].data[1] = rand() % 110; // Placeholder coolant temp gen

    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
}