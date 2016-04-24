//#include <Wire.h>
#define DELAY_TIME 20
//LiquidCrystal lcd(A7, A1, A2, A3, 11, A5);
#define step_pin 6 // Steps pin on drv8825
#define dir_pin 5  // Direction pin on drv8825
#define SLEEP 7    // SLEEP pin on drv8825
#define MIN_POS 0// Ref point
#define MAX_POS 1023
int buttonState = 0;
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
    targetPos = !digitalRead(pushButton1) * 1000 + !digitalRead(pushButton2) * 2000 + !digitalRead(pushButton3) * 3000;
    Serial.println(targetPos);


  delay(10);        // delay in between reads for stability
}
