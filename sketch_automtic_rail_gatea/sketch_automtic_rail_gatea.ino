#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int ir1 = 3;   // IR Sensor 1 (Train Approaching)
int ir2 = 4;   // IR Sensor 2 (Train Leaving)

bool gateClosed = false;

void setup() {
  servoLeft.attach(6);   // Left Gate
  servoRight.attach(5);  // Right Gate

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

  openGate();  // Open initially

  Serial.begin(9600);
}

void loop() {
  // Train is coming
  if (digitalRead(ir1) == LOW && !gateClosed) {
    Serial.println("Train Approaching... Closing Gate");
    closeGate();
    gateClosed = true;
    delay(100);
  }

  // Train is leaving - wait till train fully passes
  if (digitalRead(ir2) == LOW && gateClosed) {
    Serial.println("Train Detected at IR2... Waiting for full pass...");

    // Wait until IR2 becomes HIGH and stays HIGH for 2 seconds
    while (true) {
      if (digitalRead(ir2) == HIGH) {
        delay(1000);  // Wait 2 sec to ensure no bogie left

        if (digitalRead(ir2) == HIGH) {
          Serial.println("Train Fully Passed. Opening Gate...");
          openGate();
          gateClosed = false;
          break;
        }
      }
      delay(100);  // Short delay for sensor polling
    }
  }

  delay(100);
}

void closeGate() {
  servoLeft.write(0);     // Close position
  servoRight.write(0);    // Close position
  Serial.println("Gate Closed");
}

void openGate() {
  servoLeft.write(90);    // Open position
  servoRight.write(90);   // Open position
  Serial.println("Gate Opened");
}
