#include "config.hpp"
#include "screen.hpp"
#include <Adafruit_SSD1306.h>

//Wokwi was the goat for testing this
// I might consider moving this to a class idk

int leftAlign = SCREEN_WIDTH/5;
int row0 = 0;
int row1 = 8;
int row2 = 16;
int row3 = 24;
int row4 = 32;
int row5 = 40;
int row6 = 48;
int row7 = 56;

// Refresh rate variables
double screenTickStart = 0.0;
double screenDeltaTime = 0.0;

void initScreen(Adafruit_SSD1306 *pScreen) {

    pScreen->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    pScreen->clearDisplay();
    pScreen->setTextColor(SSD1306_WHITE);
    pScreen->print("Init :D");
    pScreen->display();
    screenTickStart = toSec(micros());
}

//Order of top left, top right, bottom right, bottom left
// A          B
// D          C
// REMINDER TO USE SINGLE QUOTES
void displayButtons(Adafruit_SSD1306 *pScreen, char A, char B, char C, char D) {
    pScreen->setTextSize(1);

    pScreen->setCursor(0, row0);
    pScreen->print(A);

    pScreen->setCursor(SCREEN_WIDTH - 8, row0);
    pScreen->print(B);

    pScreen->setCursor(SCREEN_WIDTH - 8, row7);
    pScreen->print(C);

    pScreen->setCursor(0, row7);
    pScreen->print(D);
}


void updateScreen(Adafruit_SSD1306 *pScreen, enum RTSTATES state) {

    screenDeltaTime = toSec(micros()) - screenTickStart;
    
    if (screenDeltaTime >= SCREEN_REFRESH_RATE) {
        pScreen->clearDisplay();

        switch (state) {
            case INIT:
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("INIT GYRO");
                pScreen->println("Don't Move :)");
                break;
            //i might add dTheta for the BMI here just so we can see the value
            case IDLE:
                displayButtons(pScreen, 'E', 'A', 'L', 'R');

                pScreen->setCursor(leftAlign, row0);
                pScreen->print("NOT READY");

                pScreen->setCursor(leftAlign, row1);
                pScreen->print("TARGET TIME:");
                pScreen->setCursor(leftAlign, row2);
                pScreen->print(pathInfo.targetTime);

                pScreen->setCursor(leftAlign, row3);
                pScreen->print("X OFFSET");
                pScreen->setCursor(leftAlign, row4);
                // NOT ADDED TO PATHINFO YET BUT I'LL ADD LATER
                pScreen->print(pathInfo.XOffset);

                pScreen->setCursor(leftAlign, row5);
                pScreen->print("Y OFFSET");
                pScreen->setCursor(leftAlign, row6);
                // NOT ADDED TO PATHINFO YET BUT I'LL ADD LATER
                pScreen->print(pathInfo.YOffset);
                break;
            
            case READY:
                displayButtons(pScreen, 'E', 'A', 'L', 'R');

                pScreen->setCursor(leftAlign, row0);
                pScreen->print("READY");

                pScreen->setCursor(leftAlign, row1);
                pScreen->print("TARGET TIME:");
                pScreen->setCursor(leftAlign, row2);
                pScreen->print(pathInfo.targetTime);

                pScreen->setCursor(leftAlign, row3);
                pScreen->print("X OFFSET");
                pScreen->setCursor(leftAlign, row4);
                pScreen->print(pathInfo.XOffset);

                pScreen->setCursor(leftAlign, row5);
                pScreen->print("Y OFFSET");
                pScreen->setCursor(leftAlign, row6);
                pScreen->print(pathInfo.YOffset);
                break;

            case RUNNING:
                pScreen->setTextSize(3);
                pScreen->setCursor(0, 0);
                pScreen->print("RUNNING");
                break;

            case END_RUN:
                //Reminder to add end time for run and BMI dTheta
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("RUN ENDED");
                break;
            
            case STOPPED:
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("STOPPED");
                break;
            
            case SD_ERROR:
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("SD ERROR :(");
                break;
                
            case FILE_ERROR:
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("FILE ERROR :(");
                break;

            case IMU_ERROR:
                pScreen->setTextSize(2);
                pScreen->setCursor(0, 0);
                pScreen->println("IMU ERROR :(");
                break;
            
            // I'll do the adjustment menus later

            case TESTING_TURNS:
                pScreen->setTextSize(1);
                pScreen->setCursor(0, 0);
                pScreen->println("Testing Turns");
                // I'll add theta later
                break;

        }
        pScreen->display();
        screenTickStart = toSec(micros());
    }

}
