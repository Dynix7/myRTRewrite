#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "config.hpp"
#include "BMIHelper.hpp"
#include <AccelStepper.h>

class Controller {
    private:
        //Motors
        AccelStepper *stepperL = nullptr;
        AccelStepper *stepperR = nullptr;

        //BMIHelper Class
        BMIHelper *BMI = nullptr;

        //Pathing Information
        struct PATHINFO *pathInfo = nullptr;
        double pathStartTime = 0.0;

        //Speed and Acceleration
        double speed = MAX_VEL;
        double acceleration = MAX_ACC;

        //Current State
        enum CONTROLLERSTATES state = SETUP;
    public:

    //Constructor ik format look bad but whatever
        Controller(
            AccelStepper *pStepperL, 
            AccelStepper *pStepperR, 
            BMIHelper *pBMI, 
            struct PATHINFO *pPathInfo
        );

        void controllerInit();

        void controllerUpdate();

        void turnTheta(double theta);

        void moveDistance(double distance);

}
#endif