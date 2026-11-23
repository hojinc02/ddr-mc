#ifndef _ADCSENSORS_H_
#define _ADCSENSORS_H_

#include <avr/io.h>

#ifndef PRESS_THRESHOLD
#error "PRESS_THRESHOLD must be defined"
#endif

#ifndef RELEASE_THRESHOLD
#error "RELEASE_THRESHOLD must be defined"
#endif

#if RELEASE_THRESHOLD >= PRESS_THRESHOLD
#error "RELEASE_THRESHOLD must be lower than PRESS_THRESHOLD"
#endif

void adc_init(void);         // Call at startup for analog pin init
uint8_t scan_sensors(void);  // Scan analog pins

#endif