#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <FastLED.h>

//
// -------- LED Grid Settings --------
//

// Grid layout: NUM_COLS vertical LED strips, each with NUM_ROWS LEDs
#define NUM_COLS 12
#define NUM_ROWS 118
#define LEDS_PER_STRIP NUM_ROWS

// Data pins used for each column (must match physical wiring)
#define DATA_PINS {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}

// Macro for resetting the LED grid to soft white background after effects
#define DEFAULT_RESET() fadeAllToColor(SUNLIGHT_NEUTRAL, 15, 10)

// Global LED matrix: [column][row]
extern CRGB leds_arr[NUM_COLS][LEDS_PER_STRIP];
extern const int dataPins[NUM_COLS];

// Sunlight tone presets
extern CRGB SUNLIGHT_NEUTRAL;
extern CRGB SUNLIGHT_MIDDAY;
extern CRGB SUNLIGHT_WARM;


//
// -------- Function Declarations --------
//

// Basic LED control
void lightPixel(int row, int col, CRGB color);
void lightPixelWithNeighbors(int row, int col, CRGB color);
void fadeAllToColor(CRGB targetColor, int steps, int delayMs);

// Geometric lighting effects
void expandCircle(int centerRow, int centerCol, CRGB color, int maxRadius, int delayMs);
void expandEllipse(int centerRow, int centerCol, CRGB color, int radiusX, int radiusY, int delayMs);

// Sequential patterns
void progressiveColumnLighting(int delayMs, CRGB color);
void lightUpColumnsOneByOne(int delayMs, CRGB color);

// Dynamic wave-based animations
void fishTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles);
void doubleFinTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles);

// Serial command interface
void handleSerialCommand(String input);
CRGB getColorFromName(String name);
int getCommandCode(String cmd);

#endif
