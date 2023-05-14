#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

void Display_Update_SetOverload(bool is_true);
void Display_Update_SetVoltage(bool sign, uint8_t integer, uint8_t fraction);

#endif  // DISPLAY_H
