#include <Wire.h>
#include <ArduinoEigenDense.h>
#include <Adafruit_SSD1306.h>

//ill finish boring includes later
#include "controller.hpp"
#include "BMIHelper.hpp"
#include "screen.hpp"
#include "SD.hpp"
#include "config.hpp"
#include "misc.hpp"

using namespace Eigen;

enum RTSTATES STATE = INIT;
struct PATHINFO pathInfo;

// Do object construcots later

Adafruit_SSD1306 SCREEN(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200);
  delay(250);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000); 

  pinSetup();
  digitalWrite(SPREAD, HIGH); // Sets to SpreadCycle-REMOVE IF HARDCODED
  digitalWrite(STEP_EN, HIGH); // DISABLES TMC2209 for now make sure to renable later

  /*Dac voltage, 
  154 is set as the value resulting in 2 volts out
  Adjust this depending on the motor and the resistance 
  of the sense resistors*/
  // I'll move this to a function later
  Wire.beginTransmission(DAC_ADDRESS);
  Wire.write(0b00001001);
  Wire.write(0b10100000);
  Wire.endTransmission();

  //Finish later
}

void loop() {


}
