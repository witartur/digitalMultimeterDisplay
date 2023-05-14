#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "digital_multimeter.h"
#include "support.h"


/* DIGITAL MULTIMETER TESTS */
static void SetDataForTest(float gain, float offset_volts, uint16_t adc_average_value) {
    DMM_SetCalibData(gain, offset_volts);
    DMM_Update_Voltage(adc_average_value);
}

static void test_VolageCalculationShouldBeCorrect() {
    SetDataForTest(1.2, 0.200, 500);
    float voltage = DMM_GetVoltage();
    assert(voltage >= -7.2257 && voltage <= -7.2256);

    SetDataForTest(1.2, 0.200, 2047);
    voltage = DMM_GetVoltage();
    assert(voltage >= 0.199 && voltage <= 0.201);

    printf("VolageCalculationShouldBeCorrect PASSED\n");
}

static void test_VolageCalculationShouldBeInCorrect() {
    SetDataForTest(1.2, 0.200, 500 );
    float voltage = DMM_GetVoltage();
    assert((voltage <= -7.2257 || voltage >= -7.2256) == false);

    SetDataForTest(1.2, 0.200, 2047);
    voltage = DMM_GetVoltage();
    assert((voltage <= 0.199 || voltage >= 0.201) == false);

    printf("VolageCalculationShouldBeInCorrect PASSED\n");
}

static void Digital_Multimeter() {
    test_VolageCalculationShouldBeCorrect();
    test_VolageCalculationShouldBeInCorrect();
}

/* SUPPORT TESTS */
static struct {
    millisec last_uptime;
    int timer_expiration_no;
    volatile bool timer_activity_flag;
} ctx = {0};

static bool IsFirstCall() {
    if(ctx.timer_expiration_no < 1) {
        ctx.timer_expiration_no++;
        return true;
    }
    return false;
}

static void TimerTimeoutCallback(void) {
    if(IsFirstCall())
        return;

    if(ctx.timer_expiration_no > 20) {
        ctx.timer_expiration_no = 0;
        ctx.timer_activity_flag = false;
        return;
    }

    millisec current_uptime = Uptime_GetCurrentUptime();
    assert(current_uptime - ctx.last_uptime == 100);
    ctx.last_uptime = current_uptime;
    ctx.timer_expiration_no++;
}

static void test_PeriodicTimerShouldExpireInCorrectTime() {
    ctx.last_uptime = Uptime_GetCurrentUptime();
    ctx.timer_activity_flag = true;

    Support_SimulatePeriodicTimer(100, TimerTimeoutCallback, &ctx.timer_activity_flag);
    printf("PeriodicTimerShouldExpireInCorrectTime PASSED\n");
}

static void test_SeparationIntegerAndFractionFromFloatShouldBeCorrect() {
    uint8_t integer = 0;
    uint8_t fraction = 0;

    Support_SeparateIntegerAndFractionFromFloat(-7.286, &integer, &fraction);
    assert(integer == 7 && fraction == 29);

    Support_SeparateIntegerAndFractionFromFloat(0.044, &integer, &fraction);
    assert(integer == 0 && fraction == 4);

    Support_SeparateIntegerAndFractionFromFloat(0.045, &integer, &fraction);
    assert(integer == 0 && fraction == 5);

    Support_SeparateIntegerAndFractionFromFloat(8.001, &integer, &fraction);
    assert(integer == 8 && fraction == 0);

    printf("SeparationIntegerAndFractionFromFloatShouldBeCorrect PASSED\n");
}

static void Support() {
    test_PeriodicTimerShouldExpireInCorrectTime();
    test_SeparationIntegerAndFractionFromFloatShouldBeCorrect();
}

int main() {
    Digital_Multimeter();
    Support();
}
