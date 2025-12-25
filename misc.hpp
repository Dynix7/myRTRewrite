#ifndef MISC_H
#define MSIC_H

// Distance and motor step conversions
int mmToSteps(float distance);

float stepsTomm(int steps);

// Time calculations
double ToSec(unsigned long micro);

//Angle Calculations
double toRad(double degrees);

double limitRad(double radians); // Keeps radians in range ex a turn of 4pi is 0



void beep();

void pinSetup();

#endif