#define IR_SENSOR 2
#define RELAY_PIN 3
#define BUZZER 4
#define LED 5

void setup() {
  pinMode(IR_SENSOR, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  // Default state
  digitalWrite(RELAY_PIN, LOW);   // Motor OFF
  digitalWrite(BUZZER, HIGH);     // Buzzer OFF (active LOW)
  digitalWrite(LED, LOW);         // LED OFF
}

void loop() {
  int irValue = digitalRead(IR_SENSOR);

  if (irValue == HIGH) {
    // Object detected
    digitalWrite(RELAY_PIN, LOW);    // Motor OFF
    digitalWrite(BUZZER, LOW);       // Buzzer ON (active LOW)
    digitalWrite(LED, HIGH);         // LED ON
  } else {
    // No object
    digitalWrite(RELAY_PIN, HIGH);   // Motor ON
    digitalWrite(BUZZER, HIGH);      // Buzzer OFF
    digitalWrite(LED, LOW);          // LED OFF
  }

  delay(100);
}
