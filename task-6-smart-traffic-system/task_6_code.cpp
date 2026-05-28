const int redTlight = 2;
const int yellowTlight = 3;
const int greenTlight = 4;
const int redPed = 5;
const int greenPed = 6;
const int irPin = 8;      
const int trigPin = 9;   
const int echoPin = 10;   
const int normalGreenDuration = 6000;
const int normalYellowDuration = 2000;
const int fastYellowDuration = 2000;
const int pedestrianGreenDuration = 4000;
const int redYellowDelay = 1000;
const int safetyDistance = 50;

enum TrafficState {
  GREEN,
  YELLOW,
  RED,
  RED_TO_GREEN
};

TrafficState state = GREEN;
bool pedestrianRequest = false;
unsigned long stateStartTime = 0;
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;
  return distance;
}

void setup() {
  pinMode(redTlight, OUTPUT);
  pinMode(yellowTlight, OUTPUT);
  pinMode(greenTlight, OUTPUT);
  pinMode(redPed, OUTPUT);
  pinMode(greenPed, OUTPUT);
  pinMode(irPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  state = GREEN;
  digitalWrite(greenTlight, HIGH);
  digitalWrite(yellowTlight, LOW);
  digitalWrite(redTlight, LOW);
  digitalWrite(redPed, HIGH);
  digitalWrite(greenPed, LOW);
  stateStartTime = millis();
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();
  if (digitalRead(irPin) == LOW) {  
    pedestrianRequest = true;      
  }
  long distance = measureDistance();
  bool vehiclePresent = (distance > 0 && distance < safetyDistance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Vehicle Present: ");
  Serial.println(vehiclePresent);
  switch (state) {
    case GREEN:
      digitalWrite(greenTlight, HIGH);
      digitalWrite(yellowTlight, LOW);
      digitalWrite(redTlight, LOW);
      digitalWrite(redPed, HIGH);
      digitalWrite(greenPed, LOW);
      if ((pedestrianRequest && currentTime - stateStartTime >= 2000) ||
          (currentTime - stateStartTime >= normalGreenDuration)) {
        state = YELLOW;
        stateStartTime = currentTime;
      }
      break;
    case YELLOW:
      digitalWrite(greenTlight, LOW);
      digitalWrite(yellowTlight, HIGH);
      digitalWrite(redTlight, LOW);
      if (pedestrianRequest && currentTime - stateStartTime >= fastYellowDuration) {
        state = RED;
        stateStartTime = currentTime;
      } 
      else if (!pedestrianRequest && currentTime - stateStartTime >= normalYellowDuration) {
        state = RED;
        stateStartTime = currentTime;
      }
      break;
    case RED:
      digitalWrite(yellowTlight, LOW);
      digitalWrite(redTlight, HIGH);
      if (!vehiclePresent) {
        digitalWrite(redPed, LOW);
        digitalWrite(greenPed, HIGH);
      } else {
        digitalWrite(redPed, HIGH);
        digitalWrite(greenPed, LOW);
        stateStartTime = currentTime; 
        break;
      }
      if (currentTime - stateStartTime >= pedestrianGreenDuration) {
        state = RED_TO_GREEN;
        stateStartTime = currentTime;
        pedestrianRequest = false;
      }
      break;
    case RED_TO_GREEN:
      digitalWrite(redTlight, LOW);
      digitalWrite(yellowTlight, HIGH);
      digitalWrite(redPed, HIGH);
      digitalWrite(greenPed, LOW);
      if (currentTime - stateStartTime >= redYellowDelay) {
        digitalWrite(yellowTlight, LOW);
        digitalWrite(greenTlight, HIGH);
        state = GREEN;
        stateStartTime = currentTime;
      }
      break;
  }
}
