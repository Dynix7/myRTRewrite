#ifndef MISC_H
#define MSIC_H

#include <ArduinoEigenDense.h>
using namespace Eigen;


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


//horrible switch-case chain for cordinate conversion
Vector2f toCordinate(char X, char Y);


#endif