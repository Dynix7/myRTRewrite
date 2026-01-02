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
    digitalWrite(STEP_EN, HIGH);
    state = END;
}

void Controller::updateIndexes() {
    if (pathInfo->targetIndex < pathInfo->lastIndex) {
        pathInfo->targetIndex++;
    }
    pathInfo->currentIndex++;
}

enum CONTROLLERSTATES Controller::getCurrentState() {
    return state;
}



// I might add a few .isRunning checks in replacement of the mutex but it shouldn't be needed
void Controller::turnTheta(double theta) {
    int maxAngSpeed = mmToSteps(MAX_ANG_VEL * WHEEL_RADIUS);
    int maxAngAccel = mmToSteps(MAX_ANG_ACC * WHEEL_RADIUS);

    // Finds arc length
    int steps = mmToSteps(0.5 * TRACK_WIDTH * theta); // Simplified ver of circumfrence * (radians/2*PI)

    stepperL->setMaxSpeed(maxAngSpeed);
    stepperR->setMaxSpeed(maxAngSpeed);
    stepperL->setAcceleration(maxAngAccel);
    stepperR->setAcceleration(maxAngAccel);

    stepperL->move(-steps);
    stepperR->move(steps);

}

void Controller::moveDistance(double distance) {
    int maxSpeed = mmToSteps(speed);
    int maxAccel = mmToSteps(acceleration);

    int steps = mmToSteps(distance);

    stepperL->setMaxSpeed(maxSpeed);
    stepperR->setMaxSpeed(maxSpeed);
    stepperL->setAcceleration(maxAccel);
    stepperR->setAcceleration(maxAccel);

    stepperL->move(steps);
    stepperR->move(steps);

}

void Controller::controllerUpdate() {
    BMI->updateGyro();

    switch (state) {
        case SETUP:
            break;

        case END:
            break;

        case SETMOVE:

            speed = MAX_VEL;
            acceleration = MAX_ACC;

            //Calculates distance to next point
            Vector2f currentPos = pathInfo->PATH[pathInfo->currentIndex];
            Vector2f targetPos = pathInfo->PATH[pathInfo->targetIndex];
            double distance = getDistance(targetPos, currentPos);


            // Checks if the next index is the last index, then it'll adjust speed
            if (pathInfo->targetIndex == pathInfo->lastIndex) {

                double timeTaken = toSec(micros()) - pathStartTime;
                double timeLeft = pathInfo->targetTime - timeTaken;

                //Gets speed required to meet target, if lower than max speed then it'll set speed to it
                double neededSpeed = getNeededSpeed(timeLeft, distance);    
                if (neededSpeed <= MAX_VEL) {
                    speed = neededSpeed;
                } else {
                    speed = MAX_VEL;         
                }
                //Reduces distance so dowel is on top of point 
                distance -= DIST_TO_DOWEL;
            }
        
            moveDistance(distance);
            state = MOVEMENT;
            break;


        case MOVEMENT:
            //Moves the motors
            stepperL->run();
            stepperR->run();
            // When movement done then go to FinishMovement state
            if (!stepperL->isRunning() && !stepperR->isRunning()) {
                state = FINISHMOVE;
            }
            break;


        case FINISHMOVE:
            //Advances Indexes
            updateIndexes();

            // Checks if it has reached the end
            if (pathInfo->currentIndex == pathInfo->lastIndex) {
                state = END;
            } else {
                state = SETTURN;
            }
            break;


        case SETTURN:
            Vector2f currentPos = pathInfo->PATH[pathInfo->currentIndex];
            Vector2f targetPos = pathInfo->PATH[pathInfo->targetIndex];

            //Calculates the angle to get to target using tan()
            double deltaTheta = getAngleBetween(targetPos, currentPos);
            deltaTheta = limitRad(deltaTheta);

            //Updates absolute target theta
            targetTheta += deltaTheta;
            targetTheta = limitRad(targetTheta);

            turnTheta(deltaTheta);
            state = TURNING;
            break;

        
        case TURNING:
            stepperL->run();
            stepperR->run();

            if (!stepperL->isRunning() && !stepperR->isRunning()) {
                state = FINISHTURN;
            }
            break;
        
        case FINISHTURN:
            // Checks to see how off the movement was (Closed loop feedback i think thats what its called)
            // If less than .1 radians off then will continue, else it'll turn that amount
            double thetaOff = targetTheta - (BMI->getTheta()); 

            if (abs(thetaOff) < 0.1) {
                state = SETMOVE;
            } else {
                turnTheta(thetaOff);
                state = TURNING;
            }
            break;
   
    }


}