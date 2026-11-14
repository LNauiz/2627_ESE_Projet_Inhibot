#ifndef TEST_H
#define TEST_H

#include <stdint.h>

void setup_rgb(void);
void set_led_hsv(uint8_t index, uint8_t h, uint8_t s, uint8_t v);
void loop_rgb(void);

#endif
