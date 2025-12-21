#include "SD.hpp"

#include <FS.h>
#include <SPI.h>
#include <SD.h>

#include "config.hpp"


void initSD() {

    SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
    
    if (!SD.begin(SD_CS, SPI)) {
        Serial.println("SD begin failed");
    }

}

void readSD(Eigen::Vector2f *pPATH[]) {

    File file = SD.open(PATH_FILE);
    
    if (!file) {
        Serial.println("File cooked")
    }



}


void writeSD(const char *path, const char *text);