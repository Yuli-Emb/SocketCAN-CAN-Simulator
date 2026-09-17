#include "update.h"

ecu_node ecu_nodes[] = {
    {.can_id = 0x01, .ms = 10, .name = "Engine ECU"},
    {.can_id = 0x0A, .ms = 20, .name = "ABS/Brake ECU"},
    {.can_id = 0x32, .ms = 50, .name = "Body Module"},
    {.can_id = 0x64, .ms = 100, .name = "Infotainment"},
    {.can_id = 0x2C, .ms = 250, .name = "Diagnostic tool"}
};