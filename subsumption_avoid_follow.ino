//include necessary libraries
#include <AFMotor.h>

//initialize pins for sensors
const int infraredPin1 = A0;
const int infraredPin2 = A1;
const int ultrasoundTrig = 3;
const int ultrasoundEcho = 4;

//initialize motor objects
AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

//initialize variables
int infrared1Value = 0;
int infrared2Value = 0;
long ultrasoundDuration, distance;
int speed = 150;

void setup() {
  //initialize serial communication for debugging
  Serial.begin(9600);

  //initialize motor speeds
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed);
}

void loop() {
  //read sensor values
  infrared1Value = analogRead(infraredPin1);
  infrared2Value = analogRead(infraredPin2);
  ultrasoundDuration = pulseIn(ultrasoundEcho, HIGH);
  distance = ultrasoundDuration * 0.034 / 2;

  //obstacle avoidance
  if(distance < 10) {
    Serial.println("Obstacle Detected!");
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
    delay(1000);
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
    delay(1000);
  }
  //line following
  else if(infrared1Value < 300 && infrared2Value > 300) {
    Serial.println("Following Line!");
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  }
  else if(infrared2Value < 300 && infrared1Value > 300) {
    Serial.println("Following Line!");
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  }
  else {
    Serial.println("Lost Line!");
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
    delay(1000);
  }
}
