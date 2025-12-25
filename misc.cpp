#include <Arduino.h>
#include "misc.hpp"
#include "config.hpp"

// Distance Related Calculations
int mmToSteps(float distance) {
    return (distance/(TWO_PI*WHEEL_RADIUS)) * STEPS_PER_REV;
}

float stepsTomm(int steps) {
        return ((float)steps/(STEPS_PER_REV)) * TWO_PI * WHEEL_RADIUS;
}


// Time Related Calculations
double ToSec(unsigned long micro) {
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
    while (radians < PI) {
        radians += TWO_PI;
    }
    return radians;
}




void beep() {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, HIGH);
}


void pinSetup() {
    //FINISH LATER
    // Button Init
    pinMode(BTN_0, INPUT);
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);

    
}

