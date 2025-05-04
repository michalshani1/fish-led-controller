#include "led_controller.h"  // brings in all LED and serial logic


void setup() {
  Serial.begin(9600);

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
  // Fade to neutral sunlight
  fadeAllToColor(CRGB(255, 244, 229), 30, 40); // NEUTRAL
  delay(1000);
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // removes \r or space
    if (command.startsWith("expandEllipse")) {
      int firstComma = command.indexOf(',');
      int secondComma = command.indexOf(',', firstComma + 1);

      if (firstComma != -1 && secondComma != -1) {
        int x = command.substring(firstComma + 1, secondComma).toInt();
        int y = command.substring(secondComma + 1).toInt();
      expandEllipse(y, x, CRGB::Black, 5, 30, 50); // y=row, x=col
      }
    }  
  }
  FastLED.show(); // or wherever your LED update goes
}


  // // Expand black circle in the middle
  // expandCircle(59, 6, CRGB::Black, 5, 10);
  // delay(1000);

  // // Fade to midday sunlight
  // fadeAllToColor(CRGB(255, 250, 240), 30, 40); // MIDDAY
  // delay(1000);

  // // Expand ellipse from left side
  // expandEllipse(20, 5, CRGB::Black, 6, 10, 25);
  // delay(1000);

//   fishTailEffect(CRGB::White, 12, 10.0, 4);  // Color, amplitude, speed, cycles
//   delay(1000);


//   // doubleFinTailEffect(CRGB::Cyan, 10, 10.0, 3);
//   // delay(1000);

//   // Light a single pixel and its neighbors
//   lightPixelWithNeighbors(50, 6, CRGB::Red);
//   delay(1000);

//   // Progressive column fill
//   progressiveColumnLighting(100, CRGB::Blue);\
//   delay(1000);

//   // Light columns one by one
//   lightUpColumnsOneByOne(200, CRGB::Green);
//   delay(1000);
// }
