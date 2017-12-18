
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

int vitesse;
float lum1;
float lum2;
float tolerance;

void setup(){
  Serial.begin(9600);
  Serial.println("Stepper starts!");
  AFMS.begin(); 

  myMotor->setSpeed(10);
}


void loop(){

  lum1 = float(analogRead(A0))/1023.0*100;
  lum2 = float(analogRead(A1))/1023.0*100;
  float diff = abs(lum1-lum2);


  Serial.print("A0 = ");
  Serial.print(lum1);
  Serial.print(" ------- A1 = ");
  Serial.print(lum2);
  Serial.print("------- A1 - A0 : ");
  Serial.println(diff);


  //définition de la valeur de la tolérance
  if(lum1 <= 1 && lum2 <= 1){
    tolerance = 0.1;
  }
  else if((lum1 <= 5) && (lum1 > 1) && (lum2 <= 5) && (lum2 > 10)){
    tolerance = 0.5;
  }
  else if((lum1 <= 10) && (lum1 > 5) && (lum2 <= 10) && (lum2 > 5)){
    tolerance = 1;
  }
  else{
    tolerance = 5;
  }

  
  //rotation du moteur
  if (lum1 > lum2 + tolerance){
    myMotor->step(1, FORWARD, INTERLEAVE);;
  }
  
  else if (lum1 + tolerance < lum2){ 
    myMotor->step(1, BACKWARD, INTERLEAVE);;
  }
  
  else{  
    myMotor->step(0, BACKWARD, INTERLEAVE);;
  }
}

