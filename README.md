# Fish LED Controller 🐟💡

This Arduino-based system controls a 12×118 LED grid to simulate visual stimuli for studying escape behavior in weakly electric fish (like *Gnathonemus petersii*).

## 🎯 Features

- Control 12 WS2812B LED strips (1 per column)
- Full pixel-level addressing using (row, col) coordinates
- Visual effects:
  - Expanding circle and ellipse from any point
  - Smooth fading between "sunlight" presets
  - Fish tail swish animation
  - Double-fin symmetrical wave effect
- Serial interface to receive real-time control commands from Bonsai or Python

## 🧪 Testing Modes

In the `loop()` function, built-in test patterns demonstrate all lighting effects in sequence.

## 🧠 Integration with Bonsai

The Arduino listens for serial commands like:

expandEllipse,40,6,255,0,0 fadeAllToColor,255,250,240


Use Bonsai’s `SerialPort` node + mouse or tracking data to trigger effects live.

## 📦 File Structure

- `led_serial_controller.ino` – Main Arduino file (setup + loop)
- `led_controller.h` – Declarations and shared constants
- `led_controller.cpp` – All LED and serial control logic

## 📌 Setup

- Board: Arduino Uno
- LED Type: WS2812B
- Pins: D2–D13, one per column
- Libraries: [FastLED](https://github.com/FastLED/FastLED)

