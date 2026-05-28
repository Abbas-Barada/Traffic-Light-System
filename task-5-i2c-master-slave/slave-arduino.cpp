#include <Wire.h>

const int buttonPin = 4;
const int redPed = 5;
const int greenPed = 6;

byte pedState = 0; // 0 = red, 1 = green

void setup() {
  Wire.begin(8); // slave address

  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
}

void loop() {


  int btn = digitalRead(4);
  Serial.println(btn);
  delay(200);
  

  if (pedState == 0) {
    digitalWrite(redPed, HIGH);
    digitalWrite(greenPed, LOW);
  } else {
    digitalWrite(redPed, LOW);
    digitalWrite(greenPed, HIGH);
  }
}

// ----------- I2C EVENTS ------------

void requestEvent() {
  int btn = (digitalRead(buttonPin) == LOW) ? 1 : 0;
  Wire.write(btn);
}

void receiveEvent(int howMany) {
  if (Wire.available()) {
    pedState = Wire.read();
  }
}
