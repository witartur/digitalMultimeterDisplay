#include "digital_multimeter.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

static struct {
    struct {
        float gain;
        float offset;
    } calib_data;

    int32_t adc_sample_sum;
    int16_t adc_sample_quantity;
} ctx = {0};

void DMM_SetCalibData(float gain, float offset_volts) {
    ctx.calib_data.gain = gain;
    ctx.calib_data.offset = offset_volts;
}

static float ConvertToVolts(int16_t adc_average) {
    int16_t adc_zero_volt_value = 4096 / 2 - 1;     // 12 bit ADC
    float mili_volts = 0;

    if (adc_average == adc_zero_volt_value)
        mili_volts = 0;
    else
        mili_volts = (adc_average - adc_zero_volt_value) * 4;   // 4mV resolution

    float volts = mili_volts / 1000;
    return volts;
}

static int16_t GetAdcAverage() {
    float adc_average_f = ctx.adc_sample_sum / ctx.adc_sample_quantity;
    int16_t adc_average = round(adc_average_f);

    return adc_average;
}

static float CalibrateVoltage(float voltage) {
    float voltage_calibrated = (voltage * ctx.calib_data.gain) + ctx.calib_data.offset;

    return voltage_calibrated;
}

float DMM_GetVoltage() {
    int16_t adc_average = GetAdcAverage();
    float voltage = ConvertToVolts(adc_average);
    float voltage_calibrated = CalibrateVoltage(voltage);

    ctx.adc_sample_quantity = 0;
    ctx.adc_sample_sum = 0;

    return voltage_calibrated;
}

void DMM_Update_Voltage(uint16_t adc_sample) {
    ctx.adc_sample_sum += adc_sample;
    ctx.adc_sample_quantity ++;
}
