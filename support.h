#include <stdint.h>

#include "uptime.h"

void Support_SeparateIntegerAndFractionFromFloat(float src, uint8_t *integer, uint8_t *fraction);

typedef void (*AdcSampleReceivedCallback)(uint16_t adc_sample);
void Support_SimulateAdcSampling(AdcSampleReceivedCallback callback);

typedef void (*PeriodicTimerTimeoutCallback)(void);
void Support_SimulatePeriodicTimerStart(millisec timeout, PeriodicTimerTimeoutCallback timeout_callback);
