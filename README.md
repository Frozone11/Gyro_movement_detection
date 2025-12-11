# NMove – Gyroscope Motion Detection (L3G)

A simple Arduino sketch that reads raw gyroscope data from the L3G sensor, applies smoothing, and determines whether the device is in an **ACTIVE** or **IDLE** state based on motion intensity.

---

## Features
- Reads raw gyroscope data (X, Y, Z axes)
- Converts values to degrees per second
- Computes delta movement between samples
- Applies EMA smoothing
- Detects motion using a threshold
- Prints status over Serial at 115200 baud

---

## Hardware Requirements
- Arduino (Uno, Nano, etc.)
- L3G4200D / L3GD20 gyroscope module
- I2C connection  
  - **SDA → A4**  
  - **SCL → A5**  
  - VIN → 5V  
  - GND → GND

---
## Serial Output Example
EMA=0.132  state=IDLE

EMA=1.204  state=ACTIVE

EMA=0.843  state=IDLE

---
## License 

---



