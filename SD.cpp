#include "SD.hpp"
#include "config.hpp"

#include <FS.h>
#include <SPI.h>
#include <SD.h>

#include <ArduinoEigenDense.h>
using namespace Eigen;

void initSD() {

    SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
    
    if (!SD.begin(SD_CS, SPI)) {
        Serial.println("SD init failed");
    }

}

// FORMAT IS JUST GONNA BE NUMBERS NO CHARACTERS SEPARATED BY A NEW LINE
// PATH MODE 
// TIME
// PATH POINTS
void readSD(struct PATHINFO *pPathInfo) {
    
    char buffer[4] = {0};
    Vector2f cordinate;

    File file = SD.open(PATH_FILE, FILE_READ);
    
    if (!file) {
        Serial.println("Read file cooked");
    }

    //Reads path mode (converts to integer first)
    pPathInfo->mode = atoi(file.read());  
    file.read(); //Moves to next line


    // Reads time, 5 characters
    for (int i = 0; i < 5; i++) {
        buffer[i] = file.read();
    }
    pPathInfo->targetTime = atof(buffer);
    file.read(); 


    //Reads paths
    while (file.avaliable()) {
        buffer[0] = file.read(); //Reads X
        buffer[1] = file.read(); //Reads Y
        file.read(); //Next line
    
    //Converts the characters given to a cordinate
    cordinate = toCordinate(buffer[0], buffer[1]);

    //Adjusts the first cordinate to actual starting point since the
    //robot starts off of the grid
    if (pPathInfo->lastIndex == 0) {
        pPathInfo->PATH[lastIndex] = Vector2f(cordinate(0), -DIST_TO_DOWEL);
        pPathInfo->lastIndex++;
    }

    pPathInfo->PATH[lastIndex] = cordinate;
    pPathInfo->lastIndex++;

    }

}


void createLog() {
    File file = SD.open(LOG_FILE, FILE_WRITE);

    file.println("Log Created.");
    file.close();
}

void writeSD(const char *text) {

    File file = SD.open(LOG_FILE, FILE_APPEND);

    if (!file) {
        Serial.println("Write file cooked");
        return;
    }

    file.println(text);
    file.close();


}