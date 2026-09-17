#ifndef UPDATE_H
#define UPDATE_H

#include <linux/can.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct ecu_node {
    canid_t can_id;
    int ms;
    char name[16];
    __u8 data[8];
    __u8 len;
    struct timespec last_update;
} ecu_node;

extern ecu_node ecu_nodes[];

void engine_update(struct ecu_node *n);

#endif // UPDATE_H