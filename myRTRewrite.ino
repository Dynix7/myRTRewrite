#include <Wire.h>
#include <ArduinoEigenDense.h>
//ill finish boring includes later
#include "controller.hpp"
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
  delay(500);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000); 

  pinSetup();
  digitalWrite(SPREAD, HIGH); // Sets to SpreadCycle-REMOVE IF HARDCODED
  digitalWrite(STEP_EN, HIGH); // DISABLES TMC2209 for now make sure to renable later

}

void loop() {


}
