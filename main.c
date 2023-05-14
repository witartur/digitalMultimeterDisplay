#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "digital_multimeter.h"
#include "display.h"
#include "support.h"

static struct {
    volatile bool timer_activity_flag;
    int display_updates_no;
} ctx = {
    .timer_activity_flag = true,
    .display_updates_no = 0,
};

static void DisplayVoltage(float voltage) {
    if(voltage > 10 || voltage < -10) {
        Display_Update_SetOverload(true);
    } else {
        uint8_t integer = 0;
        uint8_t fraction = 0;

        Support_SeparateIntegerAndFractionFromFloat(voltage, &integer, &fraction);
        Display_Update_SetVoltage((voltage >= 0), integer, fraction);
    }
}

static void MeasureAndDisplayVoltage() {
    Support_SimulateAdcSampling(DMM_Update_Voltage);
    float voltage = DMM_GetVoltage();
    DisplayVoltage(voltage);
    ctx.display_updates_no++;

    if(ctx.display_updates_no > 50)
        ctx.timer_activity_flag = false;
}

int main() {
    DMM_SetCalibData(1.02, 0.120);
    Support_SimulatePeriodicTimer(100, MeasureAndDisplayVoltage, &ctx.timer_activity_flag);

    return 1;
}
