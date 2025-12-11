NMove — Gyroscope Motion Activity Detection (L3G4200D / L3GD20 / L3GD20H)

NMove is an Arduino sketch that reads motion data from an L3G-series gyroscope (L3G4200D, L3GD20, L3GD20H) over I²C and detects activity states based on movement intensity.

The script computes deltas between gyro samples, applies EMA smoothing, and classifies each half-second period as either:

ACTIVE — movement detected

IDLE — low or no movement

All processing runs directly on the microcontroller and outputs results to the serial monitor.

📌 Features

✔ Reads 3-axis gyro data over I²C
✔ Converts raw readings to °/s using DPS scaling
✔ Computes movement score using Δx, Δy, Δz
✔ EMA smoothing filter to reduce noise
✔ Threshold-based ACTIVE/IDLE state detection
✔ Automatic I²C timeout recovery
✔ Lightweight, works on most Arduino boards

📂 Repository Structure
NMove/
 ├── NMove.ino          # Main Arduino sketch
 ├── README.md          # Project documentation (this file)
 └── .git/              # Git versioning folder

🛠 Hardware Requirements

Arduino (Uno, Nano, Leonardo, Mega, etc.)

L3G-series gyroscope module:

L3G4200D

L3GD20

L3GD20H

I²C wiring (SDA, SCL)

USB cable for serial monitoring

I²C Pins
Arduino	SDA	SCL
Uno/Nano	A4	A5
Mega	20	21
Leonardo	2	3

Your question:
A4 = SDA
A5 = SCL

These pins connect to the gyro’s SDA and SCL pins.

🔌 Wiring Diagram
Gyro Pin	Arduino Pin
VIN	5V (or 3.3V depending on board)
GND	GND
SDA	A4
SCL	A5
▶️ How the Script Works

Initialize the gyro using the L3G library

Read gyro values (x, y, z) in degrees per second

Compute differences between consecutive samples

Calculate motion score = √(dx² + dy² + dz²)

Smooth score using EMA filter

Compare to threshold → OUTPUT state

Print every 500 ms to Serial Monitor

📟 Example Serial Output
EMA=0.124  state=IDLE
EMA=1.203  state=ACTIVE
EMA=0.981  state=IDLE

🧠 Tunable Parameters
Parameter	Description	Default
DPS_PER_LSB	Gyro sensitivity scaling	0.00875
EMA_ALPHA	Smoothing factor	0.2
ACTIVE_THR	Threshold for ACTIVE state	0.95
delay(10)	Sample frequency	~100 Hz

Changing ACTIVE_THR alters how sensitive the activity detection is.
