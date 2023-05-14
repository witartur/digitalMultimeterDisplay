#ifndef UPTIME_H
#define UPTIME_H
#include <stdint.h>

typedef uint64_t millisec;

millisec Uptime_GetCurrentUptime(void);

#endif  // UPTIME_H
