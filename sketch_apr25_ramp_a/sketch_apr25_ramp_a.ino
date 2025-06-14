#include <Servo.h>

Servo rampServo;

int ir1 = 3;  // Approaching IR
int ir2 = 4;  // Leaving IR

bool rampIsUp = true;

void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

  rampServo.attach(6);    // Servo for the ramp

  Serial.begin(9600);

  rampServo.write(90);    // Ramp starts UP
}

void loop() {
  int sensor1 = digitalRead(ir1);  // LOW = train detected
  int sensor2 = digitalRead(ir2);

  // Train is present if either sensor detects it
  if (sensor1 == LOW || sensor2 == LOW) {
    Serial.println("Train detected → Ramp DOWN");

    if (rampIsUp) {
      for (int pos = 90; pos >= 0; pos -= 5) {
        rampServo.write(pos);
        delay(50);
      }
      rampIsUp = false;
    }

  } else {
    Serial.println("Track clear → Ramp UP");

    if (!rampIsUp) {
      for (int pos = 0; pos <= 90; pos += 5) {
        rampServo.write(pos);
        delay(50);
      }
      rampIsUp = true;
    }
  }

  delay(200);
}
