# LED Serial Controller for 12×118 Grid

This project provides a modular Arduino-based control system for a 12-column by 118-row LED grid using the WS2812B protocol and the FastLED library. It supports real-time visual effects triggered via serial commands, designed primarily for stimulus generation in behavioral experiments (e.g., fish response studies).

## 📦 System Overview

- **Hardware**: 12 vertical LED strips (WS2812B), each with 118 LEDs  
- **Controller**: Arduino Uno  R4 Minima
- **Library**: FastLED  
- **Input**: Serial commands from PC (e.g., Bonsai)  
- **Output**: Visual effects such as expanding circles, tail waves, column lighting  

## ⚙️ Setup & Wiring

- Each strip is connected to its own digital pin: **pins 2 - 13**
- The LED matrix is addressed via `[col][row]` (column-major format)
- Power supply should match the current demand of 12 x 118 LEDs

### Pin Configuration

```cpp
#define DATA_PINS {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
```

## 🔌 Installation

1. Clone or download the repository
2. Open `led_serial_controller.ino` in Arduino IDE
3. Make sure FastLED is installed:  
   **Sketch > Include Library > Manage Libraries > FastLED**
4. Select your board and COM port
5. Upload the code to the Arduino

## 🎮 Serial Commands

Use any tool that can send serial strings (Bonsai, Serial Monitor, Python) in the following format:

```
<command>,<param1>,<param2>,...
```

### Available Commands

| Command               | Description                          | Example |
|-----------------------|--------------------------------------|---------|
| `expandEllipse`       | Expanding ellipse at (row, col)      | `expandEllipse,60,6,blue` |
| `expandCircle`        | Expanding circle at (row, col)       | `expandCircle,60,6,255,100,100` |
| `lightPixel`          | Lights single pixel at (row, col)    | `lightPixel,10,2,red` |
| `lightPixelNeighbors` | Lights pixel + 4-neighbors           | `lightPixelNeighbors,30,5,white` |
| `fadeAllToColor`      | Smooth fade of entire grid to color  | `fadeAllToColor,255,255,255` |
| `setBrightness`       | Set brightness 0–255                 | `setBrightness,180` |
| `doubleFinTailEffect` | Mirrored sine wave animation         | `doubleFinTailEffect,0,0,255,10,0.3,4` |

> Color can be specified as a name (`red`, `white`, `blue`) or RGB values.

## 🌈 Built-in Color Names

Supports the following names:  
`red`, `green`, `blue`, `white`, `black`, `yellow`, `cyan`, `magenta`, `orange`, `purple`, `aqua`, `deeppink`, `deepskyblue`, `darkorange`, `gold`, `lime`

## 🧠 Notable Visual Effects

- `expandCircle` / `expandEllipse`: Stimulus spreading from a center
- `lightPixelWithNeighbors`: Mimics spatial activation
- `doubleFinTailEffect`: Simulates swimming tail motion
- `fadeAllToColor`: Daylight presets like SUNLIGHT_NEUTRAL and SUNLIGHT_WARM

## 📁 File Structure

```
led_serial_controller.ino     → Arduino sketch and setup  
led_controller.h              → LED matrix config and function declarations  
led_controller.cpp            → Lighting effect implementations  
```

## 📞 Integration Example (Bonsai)

To trigger visual patterns based on real-time fish location, send:

```
expandCircle,<row>,<col>,<r>,<g>,<b>
```

using Bonsai’s `Serial Write` node with coordinates dynamically inserted from camera tracking.