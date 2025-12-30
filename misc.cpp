#include <Arduino.h>
#include "misc.hpp"
#include "config.hpp"

#include <ArduinoEigenDense.h>
using namespace Eigen;


// MATH RELATED FUNCRIONS

// Distance Related Calculations
int mmToSteps(double distance) {
    return (distance/(TWO_PI*WHEEL_RADIUS)) * STEPS_PER_REV;
}

double stepsTomm(int steps) {
        return ((double)steps/(STEPS_PER_REV)) * TWO_PI * WHEEL_RADIUS;
}

double getDistance(Vector2f p1, Vector2f p2) {
  return sqrt(sq(p1(0) - p2(0)) + sq(p1(1) - p2(1)));
} 

double getNeededSpeed(double time, double distance) {
  double d = distance;
  double a = MAX_ACC;
  return ((a * time) - (a * sqrt(sq(time) - 4 * d / a))) / 2;
}


// Time Related Calculations
double toSec(unsigned long micro) {
    return (double) micro * 1e-6;
}


//  Angle Related Calculations
double toRad(double degrees) {
    return (double) degrees * DEG_TO_RAD;
}

double limitRad(double radians) {
    while (radians > PI) {
        radians -= TWO_PI;
    }
    while (radians < -PI) {
        radians += TWO_PI;
    }
    return radians;
}

// Ok so basically originally
double getAngleBetween(Vector2f target, Vector2f current) {
  double dY = target(1) - current(1);
  double dX = target(0) - current(0);
  return atan2(dY, dX) - (PI/2);
}

void beep() {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, HIGH);
}


void pinSetup() {

  //SPREAD MIGHT BE HARDCODED SO IF IT IS JUST REMOVE THIS
  pinMode(SPREAD, OUTPUT);
    
  // Button Init
  pinMode(BTN_0, INPUT);
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(INCR_BTN, INPUT);

  pinMode(INCR_A, INPUT);
  pinMode(INCR_B, INPUT);

  pinMode(STEP_EN, OUTPUT);
  pinMode(STEP_L, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(STEP_R, OUTPUT);
  pinMode(DIR_R, OUTPUT);

  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}


//horrible switch-case chain for cordinate conversion
Vector2f toCordinate(char X, char Y) {
    
    double pX, pY;

    switch (X) {
      case 'A':
        pX = 0;
        break;
      case 'B':
        pX = 250;
        break;
      case 'C':
        pX = 500;
        break;
      case 'D':
        pX = 750;
        break;
      case 'E':
        pX = 1000;
        break;
      case 'F':
        pX = 1250;
        break;
      case 'G':
        pX = 1500;
        break;
      case 'H':
        pX = 1750;
        break;
      case 'I':
        pX = 2000;
        break;
      case 'J':
        pX = 2250;
        break;
      case 'K':
        pX = 2500;
        break;
      default:
        Serial.printf("Bad Cordinate %c%c\n", X, Y);
        break;
    }
    switch (Y) {
      case '1':
        pY = 0;
        break;
      case '2':
        pY = 250;
        break;
      case '3':
        pY = 500;
        break;
      case '4':
        pY = 750;
        break;
      case '5':
        pY = 1000;
        break;
      case '6':
        pY = 1250;
        break;
      case '7':
        pY = 1500;
        break;
      case '8':
        pY = 1750;
        break;
      case '9':
        pY = 2000;
        break;
      case 'A':
        pY = 2250;
        break;
      case 'B':
        pY = 2500;
        break;
      default:
        Serial.printf("Bad Cordinate %c%c\n", X, Y);
        break;
    }

    return Vector2f(pX, pY);

}