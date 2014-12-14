/*
  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
*/

#include <OctoWS2811.h>

extern "C" {
#include "b3n.h"
}

const int ledsPerStrip = 11;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

s_b3n_light* lights;

void setup() {
  lights = b3n_create_lights();
  leds.begin();
  leds.show();
}

void loop() {
  b3n_update_colors(lights);
  s_b3n_light* light = lights;
  int  curr_led = 0;
  while (light != NULL)
  {
    int i;
    for (i=0; i < light->led_nbr; i++) {
      leds.setPixel(curr_led + i, light->color);
    }
    curr_led += i + (ledsPerStrip - light->led_nbr);
    light = light->next;
  }
  leds.show();
}
