#ifndef
#define SCREEN_H

#include "config.hpp"
#include <Adafruit_SSD1306.h>

// Add screen pointer to parameters maybe or just use SCREEN
void initScreen();

void displayScreen(enum RTSTATES State);

#endif