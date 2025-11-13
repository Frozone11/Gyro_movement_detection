#include <Wire.h>
#include <L3G.h>

L3G gyro;

const float DPS_PER_LSB = 0.00875f;  // for ±245 dps range
const float EMA_ALPHA   = 0.2f;      // smoothing
float lastX = 0, lastY = 0, lastZ = 0;
bool firstRead = true;
float scoreEMA = 0.0f;

const float ACTIVE_THR = 1.0f;       // ACTIVE above this
bool active = false;
unsigned long lastBeat = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1) { delay(100); }
  }

  gyro.enableDefault();
  gyro.setTimeout(50);

  Serial.println("L3G ready (active when EMA > 1.0).");
}

void loop() {
  gyro.read();

  if (gyro.timeoutOccurred()) {
    Serial.println("I2C timeout → reinit");
    gyro.init();
    gyro.enableDefault();
    gyro.setTimeout(50);
    firstRead = true;
    scoreEMA = 0.0f;
    return;
  }

  // Convert to dps
  float x = gyro.g.x * DPS_PER_LSB;
  float y = gyro.g.y * DPS_PER_LSB;
  float z = gyro.g.z * DPS_PER_LSB;

  // Delta from previous sample
  float dx = 0, dy = 0, dz = 0;
  if (!firstRead) {
    dx = x - lastX;
    dy = y - lastY;
    dz = z - lastZ;
  } else {
    firstRead = false;
  }
  lastX = x; lastY = y; lastZ = z;

  // Movement magnitude and EMA smoothing
  float score = sqrt(dx*dx + dy*dy + dz*dz);
  scoreEMA = (1.0f - EMA_ALPHA) * scoreEMA + EMA_ALPHA * score;

  // Simple threshold rule
  active = (scoreEMA > ACTIVE_THR);

  // Print to serial
  if (millis() - lastBeat > 500) {
    Serial.print("EMA=");
    Serial.print(scoreEMA, 3);
    Serial.print("  state=");
    Serial.println(active ? "ACTIVE" : "IDLE");
    lastBeat = millis();
  }

  delay(10);
}
