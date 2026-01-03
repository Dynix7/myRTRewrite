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


// Format
// PATH MODE:
// [Put the path mode here]
// TIME:
// [Put the targe time here]
// PATH POINTS:
// [Point1]
// [Point2]

// Ok so this is a little cooked so I'm gonna do a bit of a rewrite of this
bool readSD(struct PATHINFO *pPathInfo) {
    
    String line = "";
    char buffer[5] = {0};
    Vector2f cordinate;

    File file = SD.open(PATH_FILE, FILE_READ); 
    if (!file) {
        Serial.println("Read file cooked");
        return false;
    }

    //Skips PATH MODE:
    file.readStringUntil('\n');


    //Reads path mode
    line = file.readStringUntil('\n');
    line.trim();
    pPathInfo->mode = line.toInt();  

    file.readStringUntil('\n');


    // Reads time
    line = "";
    line = file.readStringUntil('\n');
    line.trim();
    pPathInfo->targetTime = line.toDouble();

    file.readStringUntil('\n');


    //Reads paths
    while (file.available()) {
        buffer[0] = file.read(); //Reads X
        buffer[1] = file.read(); //Reads Y
        file.read(); //Next line
    
        //Converts the characters given to a cordinate
        cordinate = toCordinate(buffer[0], buffer[1]);

        //Adjusts the first cordinate to actual starting point since the
        //robot starts off of the grid
        if (pPathInfo->lastIndex == 0) {
            pPathInfo->PATH[pPathInfo->lastIndex] = Vector2f(cordinate(0), -DIST_TO_DOWEL);
            pPathInfo->lastIndex++;
        }

        pPathInfo->PATH[pPathInfo->lastIndex] = cordinate;
        pPathInfo->lastIndex++;

    }
    file.close();
    return true;
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
