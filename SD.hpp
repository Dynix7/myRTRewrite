#ifndef SD_H
#define SD_H

#include <ArduinoEigenDense.h>

void initSD();

void readSD(Eigen::Vector2f *pPATH[]);

void writeSD(const char *path, const char *text);

#endif