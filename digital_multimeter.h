#include <stdint.h>
#include <stdbool.h>

void DMM_SetCalibData(float gain, float offset_volts);
void DMM_Update_Voltage(uint16_t adc_sample);
float DMM_GetVoltage();
