#ifndef MISC_H
#define MSIC_H

// Distance and motor step conversions
int mm_to_steps(float distance);

float steps_to_mm(int time);


/*Possible function here for converting from micro seconds
though im not sure why they don't just use milli seconds
and convert the final time to that, they might but idk 
i haven't fully read
*/ 
//might of set of functions dedicated to keeping time and stuff
float usToSec(uint64_t time);


float toRad(float degrees);

float limitRad(float Radians); // Keeps radians in range ex a turn of 4pi is 0



void beep();

void pinSetup();

#endif