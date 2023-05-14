#include "display.h"
#include "digital_multimeter.h"

#include <stdio.h>
#include <stdlib.h>

static void PrintTwoDigits(uint8_t value_to_print) {
    if (value_to_print < 10)
        printf("0%u", value_to_print);
    else
        printf("%u", value_to_print);
}

void Display_Update_SetOverload(bool is_true) {
    system("clear");
    printf("\n\t");
    printf("OL");
}

void Display_Update_SetVoltage(bool sign, uint8_t integer, uint8_t fraction) {
    system("clear");
    printf("\n\t");

    if(sign == false)
        printf("-");
    else
        printf("+");

    PrintTwoDigits(integer);
    printf(".");
    PrintTwoDigits(fraction);
    printf("\n");
}
