#ifndef SCREEN_H
#define SCREEN_H

#include "config.hpp"
#include <Adafruit_SSD1306.h>

//Brings the pathInfo from .ino
extern struct PATHINFO pathInfo;

// Add screen pointer to parameters maybe or just use SCREEN
void initScreen(Adafruit_SSD1306 *pScreen);

//Order of top left, top right, bottom right, bottom left
// A          B
// D          C
// REMINDER TO USE SINGLE QUOTES
void displayButtons(Adafruit_SSD1306 *pScreen, char A, char B, char C, char D);

void updateScreen(enum RTSTATES State);

#endif