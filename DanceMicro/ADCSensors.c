#include "ADCSensors.h"

#define NUM_SENSORS 4
#define PINS(X) X(A0, 7) X(A1, 6) X(A2, 5) X(A3, 4)

static const uint8_t sensor_channel[] = {
#define X(pin, ch) ch,
    PINS(X)
#undef X
};
_Static_assert(sizeof sensor_channel / sizeof sensor_channel[0] == NUM_SENSORS,
               "PINS count must equal NUM_SENSORS");

#define X(pin, ch)                                                \
  _Static_assert(RELEASE_THRESHOLD_##pin < PRESS_THRESHOLD_##pin, \
                 "RELEASE_THRESHOLD_" #pin                        \
                 " must be lower than PRESS_THRESHOLD_" #pin);
PINS(X)
#undef X

static const uint16_t press_thresholds[] = {
#define X(pin, ch) PRESS_THRESHOLD_##pin,
    PINS(X)
#undef X
};
static const uint16_t release_thresholds[] = {
#define X(pin, ch) RELEASE_THRESHOLD_##pin,
    PINS(X)
#undef X
};

void adc_init(void) {
  ADMUX = (1 << REFS0);  // Use 5V source for reference voltage
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    DIDR0 |= (1 << sensor_channel[i]);  // Disable digital input to sensor pins
  }
  ADCSRA = (1 << ADEN);  // Enable adc
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) |
            (1 << ADPS0);  // Divide 16MHz CPU clock by 128 to get 125kHz for
                           // analog read (50..200kHz for 10-bit analog acc)
}

static uint16_t adc_read(uint8_t ch) {
  ADMUX = (ADMUX & 0xE0) | (ch & 0x07);  // Clear except REFS1, REFS0, ADLAR,
                                         // and then add channel gated to 7..0
  ADCSRA |= (1 << ADSC);                 // Sample pin
  while (ADCSRA & (1 << ADSC)) {
    ;  // Wait at 125kHz until ADSC becomes 0
  }
  // Sampling done
  return ADC;  // 16-bit analog read result
}

uint8_t scan_sensors(void) {
  static uint8_t
      state;  // Current panels pressed state (last 4 bits for 4 panel)
  // Persistent state for double threshold to work
  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    uint16_t v = adc_read(sensor_channel[i]);
    if (v >= press_thresholds[i]) {
      state |= (1 << i);
    } else if (v <= release_thresholds[i]) {
      state &= ~(1 << i);
    }
  }
  return state;
}