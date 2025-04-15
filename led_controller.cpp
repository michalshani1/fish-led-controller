#include "led_controller.h"

// LED matrix and data pins
CRGB leds_arr[NUM_COLS][LEDS_PER_STRIP];
const int dataPins[NUM_COLS] = DATA_PINS;

// ---------- Named Color Lookup Table ----------
struct NamedColor {
  const char* name;
  CRGB color;
};

NamedColor colorTable[] = {
  {"red", CRGB::Red},
  {"green", CRGB::Green},
  {"blue", CRGB::Blue},
  {"white", CRGB::White},
  {"black", CRGB::Black},
  {"yellow", CRGB::Yellow},
  {"cyan", CRGB::Cyan},
  {"magenta", CRGB::Magenta},
  {"orange", CRGB::Orange},
  {"purple", CRGB::Purple},
  {"aqua", CRGB::Aqua},
  {"deeppink", CRGB::DeepPink},
  {"deepskyblue", CRGB::DeepSkyBlue},
  {"darkorange", CRGB::DarkOrange},
  {"gold", CRGB::Gold},
  {"lime", CRGB::Lime}
};
const int colorCount = sizeof(colorTable) / sizeof(NamedColor);

/**
 * Converts a color name string to its corresponding CRGB color.
 */
CRGB getColorFromName(String name) {
  name.toLowerCase();
  for (int i = 0; i < colorCount; i++) {
    if (name.equals(colorTable[i].name)) {
      return colorTable[i].color;
    }
  }
  return CRGB::White;
} // getColorFromName

/**
 * Maps a command string to a numeric code for internal use.
 */
int getCommandCode(String cmd) {
  if (cmd == "expandEllipse") return 1;
  if (cmd == "expandCircle") return 2;
  if (cmd == "lightPixel") return 3;
  if (cmd == "lightPixelNeighbors") return 4;
  if (cmd == "fadeAllToColor") return 5;
  if (cmd == "setBrightness") return 6;
  return 0;
} // getCommandCode

/**
 * Parses a serial command and executes the matching LED effect function.
 */
void handleSerialCommand(String input) {
  input.trim();
  if (input.length() == 0) return;

  int cmdEnd = input.indexOf(',');
  String command = (cmdEnd != -1) ? input.substring(0, cmdEnd) : input;
  command.trim();
  String params = (cmdEnd != -1) ? input.substring(cmdEnd + 1) : "";

  int cmdCode = getCommandCode(command);

  switch (cmdCode) {
    case 1: case 2: case 3: case 4:
    {
      int p1 = params.indexOf(',');
      int p2 = params.indexOf(',', p1 + 1);
      int p3 = params.indexOf(',', p2 + 1);
      int p4 = params.indexOf(',', p3 + 1);

      if (p1 != -1 && p2 != -1 && p3 != -1 && p4 != -1) {
        int row = params.substring(0, p1).toInt();
        int col = params.substring(p1 + 1, p2).toInt();
        int red = params.substring(p2 + 1, p3).toInt();
        int green = params.substring(p3 + 1, p4).toInt();
        int blue = params.substring(p4 + 1).toInt();
        CRGB color = CRGB(red, green, blue);

        if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
          switch (cmdCode) {
            case 1: expandEllipse(row, col, color, 6, 30, 25); break;
            case 2: expandCircle(row, col, color, 10, 10); break;
            case 3: lightPixel(row, col, color); break;
            case 4: lightPixelWithNeighbors(row, col, color); break;
          }
        }
      }
      else if (p1 != -1 && p2 != -1) {
        int row = params.substring(0, p1).toInt();
        int col = params.substring(p1 + 1, p2).toInt();
        String colorName = params.substring(p2 + 1);
        CRGB color = getColorFromName(colorName);

        if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
          switch (cmdCode) {
            case 1: expandEllipse(row, col, color, 6, 30, 25); break;
            case 2: expandCircle(row, col, color, 10, 10); break;
            case 3: lightPixel(row, col, color); break;
            case 4: lightPixelWithNeighbors(row, col, color); break;
          }
        }
      }
      break;
    }

    case 5: {
      int c1 = params.indexOf(',');
      int c2 = params.indexOf(',', c1 + 1);
      if (c1 != -1 && c2 != -1) {
        int r = params.substring(0, c1).toInt();
        int g = params.substring(c1 + 1, c2).toInt();
        int b = params.substring(c2 + 1).toInt();
        fadeAllToColor(CRGB(r, g, b), 30, 40);
      }
      break;
    }

    case 6: {
      int brightness = params.toInt();
      FastLED.setBrightness(constrain(brightness, 0, 255));
      break;
    }

    default:
      break;
  }
} // handleSerialCommand

/**
 * Lights a specific pixel on the grid.
 */
void lightPixel(int row, int col, CRGB color) {
  leds_arr[col][row] = color;
  FastLED.show();
} // lightPixel

/**
 * Lights a pixel and its four neighbors (up, down, left, right).
 */
void lightPixelWithNeighbors(int row, int col, CRGB color) {
  lightPixel(row, col, color);
  if (row > 0) lightPixel(row - 1, col, color);
  if (row < NUM_ROWS - 1) lightPixel(row + 1, col, color);
  if (col > 0) lightPixel(row, col - 1, color);
  if (col < NUM_COLS - 1) lightPixel(row, col + 1, color);
} // lightPixelWithNeighbors

/**
 * Expands outward in a circular pattern using angle and radius.
 */
void expandCircle(int centerRow, int centerCol, CRGB color, int maxRadius, int delayMs) {
  for (int radius = 0; radius <= maxRadius; radius++) {
    for (int angleDeg = 0; angleDeg < 360; angleDeg += 5) {
      float angleRad = angleDeg * PI / 180.0;
      int row = centerRow + round(radius * cos(angleRad));
      int col = centerCol + round(radius * sin(angleRad));
      if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        leds_arr[col][row] = color;
      }
    }
    FastLED.show();
    delay(delayMs);
  }
} // expandCircle

/**
 * Expands outward in an elliptical pattern using parametric math.
 */
void expandEllipse(int centerRow, int centerCol, CRGB color, int radiusX, int radiusY, int delayMs) {
  int maxR = max(radiusX, radiusY);
  for (int step = 1; step <= maxR; step++) {
    for (int row = centerRow - step; row <= centerRow + step; row++) {
      for (int col = centerCol - step; col <= centerCol + step; col++) {
        if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) continue;
        float value = pow((row - centerRow) / (float)radiusY, 2) +
                      pow((col - centerCol) / (float)radiusX, 2);
        if (value <= 1.0) {
          leds_arr[col][row] = color;
        }
      }
    }
    FastLED.show();
    delay(delayMs);
  }
} // expandEllipse

/**
 * Fills the entire LED grid with a smooth transition to a target color.
 */
void fadeAllToColor(CRGB targetColor, int steps, int delayMs) {
  for (int s = 1; s <= steps; s++) {
    float ratio = s / (float)steps;
    for (int col = 0; col < NUM_COLS; col++) {
      for (int row = 0; row < NUM_ROWS; row++) {
        leds_arr[col][row] = blend(leds_arr[col][row], targetColor, ratio * 255);
      }
    }
    FastLED.show();
    delay(delayMs);
  }
} // fadeAllToColor

/**
 * Lights up each column progressively, keeping all previous ones lit.
 */
void progressiveColumnLighting(int delayMs, CRGB color) {
  for (int col = 0; col < NUM_COLS; col++) {
    for (int row = 0; row < NUM_ROWS; row++) {
      leds_arr[col][row] = color;
    }
    FastLED.show();
    delay(delayMs);
  }
} // progressiveColumnLighting

/**
 * Lights one column fully at a time, then moves to the next.
 */
void lightUpColumnsOneByOne(int delayMs, CRGB color) {
  for (int col = 0; col < NUM_COLS; col++) {
    for (int c = 0; c < NUM_COLS; c++) {
      for (int row = 0; row < NUM_ROWS; row++) {
        leds_arr[c][row] = (c == col) ? color : CRGB::Black;
      }
    }
    FastLED.show();
    delay(delayMs);
  }
} // lightUpColumnsOneByOne

/**
 * Simulates a fish tail swish using a sine wave across columns.
 * @param baseColor - The color of the tail wave.
 * @param waveAmplitude - How far the wave sways (in rows).
 * @param waveSpeed - How quickly the wave moves (smaller is faster).
 * @param cycles - Number of complete tail swishes before stopping.
 */
void fishTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles) {
  float phase = 0.0;
  int framesPerCycle = 360 / waveSpeed;
  int totalFrames = framesPerCycle * cycles;

  for (int frame = 0; frame < totalFrames; frame++) {
    FastLED.clear();

    for (int col = 0; col < NUM_COLS; col++) {
      float wave = sin((col * 0.5) + phase); // 0.5 = horizontal stretch
      int row = NUM_ROWS / 2 + int(wave * waveAmplitude);

      if (row >= 0 && row < NUM_ROWS) {
        leds_arr[col][row] = baseColor;
      }
    }

    FastLED.show();
    delay(30);
    phase += waveSpeed * DEG_TO_RAD; // move wave forward
  }
} // fishTailEffect


/**
 * Creates a double-fin tail wave using two mirrored sine waves.
 * @param baseColor - The color of the tail.
 * @param waveAmplitude - Max distance from center line (in rows).
 * @param waveSpeed - Speed of tail wave progression.
 * @param cycles - Number of complete tail swishes.
 */
void doubleFinTailEffect(CRGB baseColor, int waveAmplitude, float waveSpeed, int cycles) {
  float phase = 0.0;
  int framesPerCycle = 360 / waveSpeed;
  int totalFrames = framesPerCycle * cycles;
  int centerRow = NUM_ROWS / 2;

  for (int frame = 0; frame < totalFrames; frame++) {
    FastLED.clear();

    for (int col = 0; col < NUM_COLS; col++) {
      float wave = sin((col * 0.5) + phase);
      int topRow = centerRow + int(wave * waveAmplitude);
      int bottomRow = centerRow - int(wave * waveAmplitude);

      if (topRow >= 0 && topRow < NUM_ROWS) {
        leds_arr[col][topRow] = baseColor;
      }
      if (bottomRow >= 0 && bottomRow < NUM_ROWS) {
        leds_arr[col][bottomRow] = baseColor;
      }
    }

    FastLED.show();
    delay(30);
    phase += waveSpeed * DEG_TO_RAD;
  }
} // doubleFinTailEffect


