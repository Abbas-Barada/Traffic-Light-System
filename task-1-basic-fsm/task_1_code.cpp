const int redPin = 2;
const int yellowPin = 3;
const int greenPin = 4;

enum lightstate { RED, YELLOW, GREEN }; 
lightstate state = RED;                  
lightstate previousstate = RED;         

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  switch (state) {
    case RED:
      digitalWrite(redPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, LOW);
      delay(5000);           
      previousstate = RED;
      state = YELLOW;        
      break;

    case YELLOW:
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(greenPin, LOW);

      if (previousstate == RED) {
        delay(5000);
        previousstate = YELLOW;
        state = GREEN;
      } else if (previousstate == GREEN) {
        delay(3000);
        previousstate = YELLOW;
        state = RED;
      }
      break;

    case GREEN:
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin, HIGH);
      delay(5000);            
      previousstate = GREEN;
      state = YELLOW;         
      break;
  }
}
