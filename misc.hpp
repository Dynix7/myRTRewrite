#ifndef MISC_H
#define MSIC_H

int mm_to_steps(float d, float r, int tpr);

float steps_to_mm(int t, float r, int tpr);

void beep();

void pinSetup();


#endif