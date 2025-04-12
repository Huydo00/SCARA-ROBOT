#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <Servo.h>

/*  MS1   MS2    MS3
    LOW   LOW    LOW    Full
    LOW   HIGH   LOW    1/4
    HIGH  HIGH   LOW    1/8
    HIGH  HIGH   HIGH   1/16
*/

/*  1 PWM = 1/4 * 1.8' = 0.45
    1 vòng 360' = 360/0.45 = 800

    X: 20-80   22-110    0.25*0.2   
    Y: 20-80   23-92     0.25*0.25
    Z: 20-90             2/9
    A: 250mm
*/
Servo myservo;
int ena = 8;
int step_X = 2 ; int dir_X = 5;
int step_Y = 3 ; int dir_Y = 6;
int step_Z = 4 ; int dir_Z = 7;
int step_A = 12 ; int dir_A = 13;

AccelStepper Step_X(1, step_X, dir_X);
AccelStepper Step_Y(1, step_Y, dir_Y);
AccelStepper Step_Z(1, step_Z, dir_Z);

#define E_X 9
#define E_Y 10
#define E_Z 11
#define E_A A3

bool gt_E_X;
bool gt_E_Y;
bool gt_E_Z;
bool gt_E_A;

void homeZ(){
  int homeZ = 0;
  Step_Z.enableOutputs();

  while(digitalRead(E_Z)){
    Serial.println(digitalRead(E_Z));
    Step_Z.moveTo(homeZ);
    homeZ ++;
    Step_Z.run();
  }
  Step_Z.setCurrentPosition(0);
  homeZ = 0;

  Step_Z.moveTo(-1800);
  while (Step_Z.distanceToGo()!=0)
  {
    Step_Z.run();
  }
  Step_Z.disableOutputs();
}

void setup() {
  Serial.begin(9600);
  pinMode(E_X, INPUT_PULLUP);
  pinMode(E_Y, INPUT_PULLUP);
  pinMode(E_Z, INPUT_PULLUP);
  pinMode(E_A, INPUT_PULLUP);

  pinMode(ena, OUTPUT);
  pinMode(step_X, OUTPUT);
  pinMode(dir_X, OUTPUT);
  pinMode(step_Y, OUTPUT);
  pinMode(dir_Y, OUTPUT);
  pinMode(step_Z, OUTPUT);
  pinMode(dir_Z, OUTPUT);
  pinMode(step_A, OUTPUT);
  pinMode(dir_A, OUTPUT);

  Step_Z.setEnablePin(8);
  Step_X.setPinsInverted(false, false, true);
  Step_Y.setPinsInverted(false, false, true);
  Step_Z.setPinsInverted(false, false, true);

  Step_X.setMaxSpeed(500);
  Step_X.setAcceleration(500);
  Step_Y.setMaxSpeed(500);
  Step_Y.setAcceleration(500);
  Step_Z.setMaxSpeed(500);
  Step_Z.setAcceleration(500);
  
  homeZ();
}

void gtE(){
  gt_E_X = digitalRead(E_X);
  gt_E_Y = digitalRead(E_Y);
  gt_E_Z = digitalRead(E_Z);
  gt_E_A = digitalRead(E_A);

  Serial.print("X:");
  Serial.print(gt_E_X);
  Serial.print("     Y:");
  Serial.print(gt_E_Y);
  Serial.print("     Z:");
  Serial.print(gt_E_Z);
  Serial.print("     A:");
  Serial.print(gt_E_A);
  Serial.println("");
  delay(1000);
}

void loop() {
}