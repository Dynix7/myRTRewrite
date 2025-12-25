#ifndef SD_H
#define SD_H

#include <ArduinoEigenDense.h>
using namespace Eigen

void initSD();

void readSD(Vector2f *pPATH[]);

void writeSD(const char *path, const char *text);

#endif