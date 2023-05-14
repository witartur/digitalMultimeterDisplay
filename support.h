#ifndef SUPPORT_H
#define SUPPORT_H

#include <stdint.h>
#include <stdbool.h>

#include "uptime.h"

void Support_SeparateIntegerAndFractionFromFloat(float src, uint8_t *integer, uint8_t *fraction);

typedef void (*AdcSampleReceivedCallback)(uint16_t adc_sample);
void Support_SimulateAdcSampling(AdcSampleReceivedCallback callback);

typedef void (*PeriodicTimerTimeoutCallback)(void);
void Support_SimulatePeriodicTimer(millisec timeout, PeriodicTimerTimeoutCallback timeout_callback, volatile bool *timer_activity_flag);

#endif  // SUPPORT_H
