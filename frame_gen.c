#include "frame_gen.h"
#include <time.h>
#include <stdlib.h>

#define DIAMETER 60
#define GEAR_RATIO 8

struct can_frame random_frame(){
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

void engine_sim(){
    ecu_nodes[0].len = 2;

    ecu_nodes[0].data[0] = rand() % 80; // Placeholder rpm gen

    ecu_nodes[0].data[1] = rand() % 110; // Placeholder coolant temp gen

    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
}

void abs_sim() {
    printf("ABS Used\n");
}

void tcs_sim() {
    printf("TCS Used\n");
}

void positive_slip(float vh_speed, float wh_speed) {
    ecu_nodes[1].data[0] = 1;
    ecu_nodes[1].data[1] = 0;

    ecu_nodes[1].data[3] = ((vh_speed - wh_speed)/(vh_speed))*100;
    if (ecu_nodes[1].data[2] > 30) {
        tcs_sim();
    }
}

void positive_slip(float vh_speed, float wh_speed) {
    ecu_nodes[1].data[0] = 0;
    ecu_nodes[1].data[1] = 1;

    ecu_nodes[1].data[3] = ((vh_speed - wh_speed)/(vh_speed))*100;
    if (ecu_nodes[1].data[2] > 30) {
        tcs_sim();
    }
}


void wheel_control() {
    ecu_nodes[1].len = 3;
    
    float rpm = ecu_nodes[0].data[0];
    float vh_speed = ((rpm / GEAR_RATIO) * 3.14 * DIAMETER * 60) / 100000;

    float wh_speed = vh_speed + (rand() % 100) - (rand() % 100);


    if (wh_speed > vh_speed) {
        positive_slip(vh_speed, wh_speed);
    }

    else if (wh_speed < vh_speed) {
        negative_slip(vh_speed, wh_speed);
    }
}

