# 🐟 Fish Tracking & LED Triggering Flow in Bonsai

This Bonsai workflow is designed to track the position of a fish (e.g., *Gnathonemus petersii*) in a behavioral experiment setup and trigger visual stimuli via an Arduino-controlled LED grid in real time.

## 🎯 Purpose

- Extract the fish's (X, Y) coordinates from live camera feeds  
- Process the image to detect the fish body position reliably  
- Send serial commands to the Arduino when a stimulus is needed (e.g., expanding circle on LED grid)

## 📷 Camera Input

- Uses **Spinnaker** cameras via `SpinView` 
- Typically uses multiple angles (top, sides), though the flow can operate with one

## 🧪 Image Processing Pipeline

### General Flow Steps:

1. **Capture Frame**  
   Real-time input from camera (`Image` node)

2. **CropPolygon**  
   Manually defined polygonal region of interest to isolate the aquarium area

3. **Grayscale Conversion**  
   Converts the cropped image to intensity-only (1 channel)

4. **RangeThreshold**  
   Filters brightness to isolate the fish's body

5. **Morphological Operator**  
   Erode/dilate cycles to remove noise and restore fish contour

6. **FindContours**  
   Identifies closed shapes in the thresholded image

7. **Binary Region Analysis → Largest Binary Region**  
   Keeps only the largest detected region (the fish)

8. **Centroid**  
   Calculates the center of the fish's detected region

9. **Rescale + Zip (X,Y)**  
   Scales the fish’s position to LED grid resolution (rows/cols)

10. **PythonTransform + SerialWriteLine**  
    Formats a command string like `expandEllipse,51,7` and sends it to the Arduino

## 🧩 Arduino Integration

Bonsai sends serial strings like:

```
expandCircle,60,6,255,244,229
```

This command triggers an expanding circle animation on the LED grid at (row=60, col=6) with a warm white color.

- The `SerialPort` node is configured with:
  - **Baud rate**: `9600`
  - **NewLine**: `\n`
  - **Port name**: Matches the Arduino COM port

## 💬 Supported Commands (sent from Bonsai)

| Function in Arduino         | Example Command                             |
|-----------------------------|---------------------------------------------|
| `expandCircle`              | `expandCircle,60,6,255,100,100`             |
| `expandEllipse`             | `expandEllipse,60,6,blue`                   |
| `lightPixel`                | `lightPixel,10,2,red`                       |
| `doubleFinTailEffect`       | `doubleFinTailEffect,0,0,255,10,0.3,4`      |
| `fadeAllToColor`            | `fadeAllToColor,255,255,255`               |
| `setBrightness`             | `setBrightness,180`                        |

## 🧠 Notes

- Ensure the fish is the most prominent object in the field of view
- CropPolygon is essential to ignore background noise or walls of the tank
- Adjust `RangeThreshold` values depending on light conditions
- Morphological steps (Erode/Dilate) are crucial for stable contour detection
- Y&X axis flip is needed to match physical LED orientation (excuted in the python script)