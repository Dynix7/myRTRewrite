#ifndef MISC_H
#define MISC_H

#include <ArduinoEigenDense.h>
using namespace Eigen;


// Distance and motor step conversions
int mmToSteps(double distance);

double stepsTomm(int steps);

double getDistance(Vector2f p1, Vector2f p2);


// Time calculations
double toSec(unsigned long micro);

double getNeededSpeed(double time, double distance);


//Angle Calculations
double toRad(double degrees);

double limitRad(double radians); // Keeps radians in range ex a turn of 4pi is 0

double getAngleBetween(Vector2f target, Vector2f current); //get back to this later


void beep();

void pinSetup();


//horrible switch-case chain for cordinate conversion
Vector2f toCordinate(char X, char Y);


#endif