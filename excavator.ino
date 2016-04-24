#define pushButton0 A0
#define pushButton1 A1
#define pushButton2 A2
#define pushButton3 A3

#define MAX_STEPS  4000//se va inmulti cu 1000
int direction;    // Variable to set Rotation (CW-CCW) of the motor
int currentPos = 0, targetPos = 0;
void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(SLEEP, OUTPUT);
  Serial.begin(9600);
  pinMode(pushButton0, INPUT);
  pinMode(pushButton1, INPUT);
  pinMode(pushButton2, INPUT);
  pinMode(pushButton3, INPUT);

  Serial.setTimeout(2000);
  digitalWrite(SLEEP, HIGH);  // Wake up EasyDriver
  delay(5);  // Wait for EasyDriver wake up

  while (analogRead(A4) > MIN_POS) {
    digitalWrite(dir_pin, HIGH);
    digitalWrite(step_pin, HIGH);
    delay(1);
    digitalWrite(step_pin, LOW);
    delay(1);   //delay for reference point - BACK
  }
  
  while (analogRead(A4) <= MIN_POS) {
    digitalWrite(dir_pin, LOW);
    digitalWrite(step_pin, HIGH);
    delay(1);
    digitalWrite(step_pin, LOW);
    delay(1);   //delay for reference point - BACK
  }
  Serial.println("initialized");
}

void loop() {

  while (targetPos > 0 && targetPos < MAX_STEPS && (analogRead(A4) > MIN_POS) && currentPos != targetPos) {

    if (currentPos > targetPos) {

      digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      // delay(2);
      digitalWrite(step_pin, LOW);
      //delay(2);
      for (int i = 0; i < DELAY_TIME; i++) analogRead(A6);
      currentPos--;
    }
    if (currentPos < targetPos) {
      digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      //delay(2);
      digitalWrite(step_pin, LOW);
      //delay(2);
      for (int i = 0; i < DELAY_TIME; i++) analogRead(A6);
      currentPos++;
    }
  }
  // set the target according to buttons
    if (!digitalRead(pushButton0)) {
    targetPos = 100;
  } 
  if (!digitalRead(pushButton1)) {
    targetPos = 200;
  }
  if (!digitalRead(pushButton2)) {
    targetPos = 300;
  }
  if (!digitalRead(pushButton3)) {
    targetPos = 400;
  }
  
  Serial.print("currentPos:");
  Serial.println(targetPos);
  Serial.print("currentPos:");
  Serial.println(currentPos);
  Serial.print("encoder:");
  Serial.println(analogRead(A4));
  delay(10);        // delay in between reads for stability
}
Status API Training Shop Blog About
© 2016 GitHub, Inc. Terms Pri
