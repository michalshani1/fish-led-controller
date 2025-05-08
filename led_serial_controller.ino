#include "led_controller.h"  // brings in all LED and serial logic

bool commandReceived = false;

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
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    handleSerialCommand(command);
    commandReceived = true;
  }

  if (!commandReceived) {
    fadeAllToColor(SUNLIGHT_NEUTRAL, 50, 10); // only fade if nothing else happened
  }

  commandReceived = false; // reset for next loop
}


//   if (Serial.available()) {
//     String command = Serial.readStringUntil('\n');
//     command.trim(); // removes \r or space

//     if (command.startsWith("expandEllipse")) {
//       int firstComma = command.indexOf(',');
//       int secondComma = command.indexOf(',', firstComma + 1);

//       if (firstComma != -1 && secondComma != -1) {
//         int x = command.substring(firstComma + 1, secondComma).toInt();
//         int y = command.substring(secondComma + 1).toInt();

//         Serial.print("Received command: expandEllipse with x=");
//         Serial.print(x);
//         Serial.print(", y=");
//         Serial.println(y);

//         expandEllipse(y, x, CRGB::Black, 5, 10, 0); // y=row, x=col
//         FastLED.show();
//       }
//     }
//   }
// }


// void loop() {
//   // Fade to neutral sunlight
//   fadeAllToColor(CRGB(255, 244, 229), 30, 40); // NEUTRAL
//   delay(1000);

//   // expandEllipse(65, 5, CRGB::Blue, 5, 10, 0);  // row=65, col=5 //cols=12 //rows=118 //expandEllipse(int centerRow, int centerCol, CRGB color, int radiusX, int radiusY, int delayMs)
//   // FastLED.show();  // Ensure the LEDs are updated

//   if (Serial.available()) {
//     String command = Serial.readStringUntil('\n');
//     command.trim(); // removes \r or space

//     if (command.startsWith("expandEllipse")) {
//       int firstComma = command.indexOf(',');
//       int secondComma = command.indexOf(',', firstComma + 1);

//       if (firstComma != -1 && secondComma != -1) {
//         int x = command.substring(firstComma + 1, secondComma).toInt();
//         int y = command.substring(secondComma + 1).toInt();

//         Serial.print("Parsed coords: x=");
//         Serial.print(x);
//         Serial.print(", y=");
//         Serial.println(y);

//         expandEllipse(y, x, CRGB::Blue, 5, 10, 0); // y=row, x=col
//         FastLED.show();  // Only needed if expandEllipse doesn't call it internally
//       }
//     }
//   }
//   FastLED.show(); // or wherever your LED update goes
// }

