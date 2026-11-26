#include "MecanumRobot.h"
MecanumRobot robot(4, 3, 6, 5, 10, 9, 12, 11);
const int trigPin = 7;
const int echoPin = 8;
int turns = 0;
const float wall_cm = 20;
const int finalMs = 4000;

void setup() {
  // put your setup code here, to run once:
  robot.begin();
  robot.setTurnTime(780);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration;
  float distance;

  //clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //send 10 microsecond pilse to trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read the echo pin
  duration = pulseIn(echoPin, HIGH);

  //convert time to distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm or ");
  Serial.print(distance / 2.54);
  Serial.println(" in");
  Serial.print("turns ");
  Serial.println(turns);

  if (distance < wall_cm && distance != 0 && turns < 4) {
    robot.stop();
    delay(10);
    robot.right(90);
    delay(10);
    turns++;
  } else if (distance < wall_cm && distance != 0 && 3 < turns < 6) {
    robot.stop();
    delay(10);
    robot.left(90);
    delay(10);
    turns++;
  } else if (turns > 5) {
    robot.forwardStart();
    delay(finalMs);
    robot.stop();
    while (true) {}
  } else {
    robot.forwardStart();
    delay(10);
  } 
}
