int ledSegments[10][7] = {
  {1,1,1,0,1,1,1}, // 0
  {0,0,1,0,0,0,1}, // 1
  {1,1,0,1,0,1,1}, // 2
  {0,1,1,1,0,1,1}, // 3
  {0,0,1,1,1,0,1}, // 4
  {0,1,1,1,1,1,0}, // 5
  {1,1,1,1,1,1,0}, // 6
  {0,0,1,0,0,1,1}, // 7
  {1,1,1,1,1,1,1}, // 8
  {0,1,1,1,1,1,1}  // 9
};
int bestTime = 999;

void displayDigit(int number, int displayId){
  for (int j = 0; j <= 6; j++){
    digitalWrite(j + 7 * displayId, ledSegments[number][j] == 0 ? LOW : HIGH);
  }
}

void resetDisplays(){
  displayDigit(0, 1);
  displayDigit(0, 0);
  digitalWrite(A1, HIGH);
  digitalWrite(A0, LOW);
}

void turnOffDisplays(){
  for (int i = 0; i <= 13; i++){
    digitalWrite(i, LOW);
  }
  digitalWrite(A4, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A0, LOW);
}

void blinkNumber(int numberToBlink){
  for (int i = 0; i < 3; i++){   
    delay(500);
    turnOffDisplays();
    delay(500);
    displayDigit(numberToBlink / 100 % 10, 1);
    displayDigit(numberToBlink / 10 % 10, 0);
    digitalWrite(A4, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A0, LOW);
  }
}

void displayTime(int timeValue){
  if (timeValue >= 1000){
    displayDigit(9, 1);
    displayDigit(9, 0);
    digitalWrite(A1, LOW);
    digitalWrite(A0, HIGH);
  } else {
    displayDigit(timeValue / 100 % 10, 1);
    displayDigit(timeValue / 10 % 10, 0);
    digitalWrite(A1, HIGH);
    digitalWrite(A0, LOW);
  }
}

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, INPUT);
  for (int i = 0; i <=13; i++){
    pinMode(i, OUTPUT);
  }
  digitalWrite(A4, HIGH);
  resetDisplays();
  digitalWrite(A3, LOW);  
}
 
void loop() {
  int currentTime;
  while (digitalRead(A5) == LOW) continue;
  resetDisplays();
  int delayTime = random(4000, 6000);
  delay(delayTime);
  unsigned long startTime = millis();
  digitalWrite(A3, HIGH);
  while (digitalRead(A5) == LOW){
    unsigned long now = millis();
    currentTime = (now - startTime); 
    displayTime(currentTime);
  }
  digitalWrite(A3, LOW);
  
  if (currentTime < bestTime){
    blinkNumber(currentTime);
    bestTime = currentTime;
  }
  
  delay(1000);
}
