#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <FastLED.h>

// -------- LED Grid Settings --------
#define NUM_COLS 12
#define NUM_ROWS 118
#define LEDS_PER_STRIP NUM_ROWS
#define DATA_PINS {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}

extern CRGB leds_arr[NUM_COLS][LEDS_PER_STRIP];
extern const int dataPins[NUM_COLS];

// -------- Function Declarations --------

// LED grid control
void lightPixel(int row, int col, CRGB color);
void lightPixelWithNeighbors(int row, int col, CRGB color);
void fadeAllToColor(CRGB targetColor, int steps, int delayMs);

// Visual effects
void expandCircle(int centerRow, int centerCol, CRGB color, int maxRadius, int delayMs);
void expandEllipse(int centerRow, int centerCol, CRGB color, int radiusX, int radiusY, int delayMs);
void progressiveColumnLighting(int delayMs, CRGB color);
void lightUpColumnsOneByOne(int delayMs, CRGB color);
void fishTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles);
void doubleFinTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles);

// Serial interface
void handleSerialCommand(String input);
CRGB getColorFromName(String name);
int getCommandCode(String cmd);

#endif
