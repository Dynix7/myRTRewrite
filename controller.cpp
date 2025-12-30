#include "controller.hpp"
#include "misc.hpp"
#include "config.hpp"
#include "BMIHelper.hpp"

#include <AccelStepper.h>
#include <ArduinoEigenDense.h>
using namespace Eigen;

Controller::Controller(
            AccelStepper *pStepperL, 
            AccelStepper *pStepperR, 
            BMIHelper *pBMI, 
            struct PATHINFO *pPathInfo): 
            stepperL(pStepperL),
            stepperR(pStepperR),
            BMI(pBMI),
            pathInfo(pPathInfo) {}


void Controller::controllerInit() {

    stepperL->setPinsInverted(true); // Rotate same direction since its flipped 180 from right motor
    stepperL->setMinPulseWidth(2);
    stepperR->setMinPulseWidth(2);

    stepperL->setCurrentPosition(0);
    stepperR->setCurrentPosition(0);
    
}   

void Controller::startPath() {
    digitalWrite(STEP_EN, LOW); 
    state = SETMOVE;
    pathStartTime = toSec(micros());
}

void Controller::endPath() {
    digiWrite(STEP_EN, HIGH);
    state = END;
}

enum CONTROLLERSTATES Controller::getCurrentState() {
    return state;
}


void Controller::turnTheta(double theta) {
    double maxAngSpeed = mmToSteps()

}

void Controller::controllerUpdate() {




}