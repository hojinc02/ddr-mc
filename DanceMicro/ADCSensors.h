#ifndef _ADCSENSORS_H_
#define _ADCSENSORS_H_

#include <avr/io.h>

#define CHECK_THRESHOLDS(pin)                                     \
  _Static_assert(RELEASE_THRESHOLD_##pin < PRESS_THRESHOLD_##pin, \
                 "RELEASE_THRESHOLD_" #pin                        \
                 " must be lower than PRESS_THRESHOLD_" #pin)

CHECK_THRESHOLDS(A0);
CHECK_THRESHOLDS(A1);
CHECK_THRESHOLDS(A2);
CHECK_THRESHOLDS(A3);

void adc_init(void);         // Call at startup for analog pin init
uint8_t scan_sensors(void);  // Scan analog pins

#endif