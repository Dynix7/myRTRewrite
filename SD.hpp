#ifndef SD_H
#define SD_H

#include "config.hpp"

#include <ArduinoEigenDense.h>
using namespace Eigen;

void initSD();

bool readSD(struct PATHINFO *pPathInfo);

void writeSD(const char *text);

void createLog();

#endif