const int ledPin = 9;
const int ledPinG = 4;
const int led2Pin = 13;
const int led2PinG = 12;

const int buttonPin = 2;

const int sensorPin = 5;
const int piezoPin = 6;

bool systemActive = false;
int lastButtonState = HIGH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(sensorPin, INPUT);
  pinMode(piezoPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(piezoPin, 0);
}

void loop() {



  int buttonState = digitalRead(buttonPin);

  // Check if button was pressed (if button state transitioned from HIGH to LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {
    analogWrite(ledPinG, 255);
    analogWrite(led2PinG, 255);
    delay(500);
    analogWrite(ledPinG, 0);
    analogWrite(led2PinG, 0);
    systemActive = !systemActive; // Toggle system state (from ON <-> OFF)
    delay(200);
    
  }
  
  lastButtonState = buttonState;

  // BEAR FUNCTIONALITY
  if (systemActive) {
    // Check if the vibration sensor is triggered
    if (digitalRead(sensorPin) == HIGH) {
      analogWrite(ledPin, 0); // Turn bear eyes off when impact/vibration occurs
      analogWrite(led2Pin, 0);
      tone(piezoPin, 1000);
      delay(50);
      tone(piezoPin, 0);
      delay(50);
      tone(piezoPin, 350);
      delay(200);
    } else {
      analogWrite(ledPin, 255);  // Keep LEDs on when no vibration
      analogWrite(led2Pin, 255);
      noTone(piezoPin);
    }
  } else {
    // If system is OFF: keep LEDs OFF regardless of sensor input
    analogWrite(ledPin, 0);
    analogWrite(led2Pin, 0);
    noTone(piezoPin);
  }
}