//////////////////////////////////////////////////////////////////
// 6/2021 R.Kincaid
// Code to use (for fun) the LED's available on
// the Adafruit Trinket M0 and Neo Trinkey. It
// just shows a color code for which ROM is in use.
// I didn't want to waste the LED's, and also it's
// handy to lower the brightness anyway...
//
// If neither of these two boards are defined, the
// function call turn into NOP's. So the code should
// still operate if built for a different Arduino
// board.
//////////////////////////////////////////////////////////////////

#include <Arduino.h>

// Decide what if any LED's are available
// The Trinket and Trinky have 1 or more LED's so
// We'll play with them for fun
#undef HAS_LED
#ifdef ADAFRUIT_TRINKET_M0
#include <Adafruit_DotStar.h>
#define DOTSTAR_DATPIN INTERNAL_DS_DATA
#define DOTSTAR_CLKPIN INTERNAL_DS_CLK
#define NUM_PIXEL 1
#define HAS_LED
Adafruit_DotStar strip =
    Adafruit_DotStar(1, DOTSTAR_DATPIN, DOTSTAR_CLKPIN, DOTSTAR_BGR);
#endif
#ifdef ADAFRUIT_NEOTRINKEY_M0
#include <Adafruit_NeoPixel.h>
#define NUM_PIXEL NUM_NEOPIXEL
#define HAS_LED
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
#endif

#ifdef HAS_LED
// define a few LED Colors
int RED = 0xFF0000;
int GREEN = 0x00FF00;
int BLUE = 0x0000FF;
int YELLOW = 0xAAAA00;
int BLACK = 0x000000;

int colors[] = {RED, GREEN, BLUE, YELLOW, BLACK};
int cur_color = BLACK;
#endif

// given a color id set all the LED's available
// to that color
void set_led(int colorid) {
#ifdef HAS_LED
  int color = colors[colorid % 4];
  for (int i = 0; i < NUM_PIXEL; ++i) {
    strip.setPixelColor(i, color);
  }
  strip.show();
#endif
}

// Initialize the strip
void setup_led() {
#ifdef HAS_LED
  strip.begin();
  strip.setBrightness(1);
  set_led(BLACK);
  strip.show();
#endif
}
