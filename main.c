#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "digital_multimeter.h"
#include "display.h"
#include "support.h"

static void DisplayVoltage(float voltage) {
    if(voltage > 10) {
        Display_Update_SetOverload(true);
        Display_Update_SetVoltage(true, 10, 0);
    }
    else if(voltage < -10) {
        Display_Update_SetOverload(true);
        Display_Update_SetVoltage(false, -10, 0);
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
}

int main() {
    DMM_SetCalibData(1.02, 0.120);
    Support_SimulatePeriodicTimerStart(100, MeasureAndDisplayVoltage);

    return 1;
}
