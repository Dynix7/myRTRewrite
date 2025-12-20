#ifndef SD_H
#define SD_H

#include <ArduinoEigenDense.h>

void initSD(int CLK, int MISO, int MOSI, int CS);

void readSD(Eigen::Vector2f *pPATH, int PATH_SIZE);


#endif