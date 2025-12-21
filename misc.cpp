#include <Arduino.h>
#include "misc.hpp"
#include "config.hpp"

int mm_to_steps(float d) {
    return (d/(TWO_PI*WHEEL_RADIUS)) * STEPS_PER_REV;
}

float steps_to_mm(int t) {
    return ((float)t/(STEPS_PER_REV)) * TWO_PI * WHEEL_RADIUS;
}

void beep() {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, HIGH);
}

void pinSetup() {

    // Button Init
    pinMode(BTN_0, INPUT);
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);

    // 
}

