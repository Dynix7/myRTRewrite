#include <Wire.h>
#include <ArduinoEigenDense.h>
//ill finish boring includes later
#include "BMIHelper.hpp"
#include "screen.hpp"
#include "SD.hpp"
#include "config.hpp"
#include "misc.hpp"

using namespace Eigen;

enum RTSTATES STATE;
struct PATHINFO pathInfo;


void setup() {

  STATE = INIT;

  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000); //Fast Mode


}

void loop() {


}
