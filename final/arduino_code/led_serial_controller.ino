/**
 * Main Arduino sketch for LED stimulus controller.
 * 
 * This file handles:
 * - Initialization of 12 LED strips (columns), each with 118 LEDs (rows)
 * - Serial communication for triggering visual effects
 * - Default idle behavior (fading to SUNLIGHT_NEUTRAL background)
 */

#include "led_controller.h"  // Includes LED matrix logic and effect functions

bool commandReceived = false;

void setup() {

  Serial.begin(9600);  // Open serial communication for command input

  // Attach each LED strip to its respective pin
  FastLED.addLeds<WS2812B, 2, GRB>(leds_arr[0], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 3, GRB>(leds_arr[1], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 4, GRB>(leds_arr[2], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 5, GRB>(leds_arr[3], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 6, GRB>(leds_arr[4], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 7, GRB>(leds_arr[5], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 8, GRB>(leds_arr[6], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 9, GRB>(leds_arr[7], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 10, GRB>(leds_arr[8], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 11, GRB>(leds_arr[9], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 12, GRB>(leds_arr[10], LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 13, GRB>(leds_arr[11], LEDS_PER_STRIP);

  FastLED.setBrightness(100);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Check for serial command
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove trailing \r or whitespace
    handleSerialCommand(command);
    commandReceived = true;
  }

  // If no serial command was received, show default ambient light
  if (!commandReceived) {
    fadeAllToColor(SUNLIGHT_NEUTRAL, 15, 10);  // Fade to soft white
  }

  commandReceived = false;  // Reset flag for next loop iteration
}
