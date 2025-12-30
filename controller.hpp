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

        double distance = 0.0;


        double targetTheta = 0.0;

        //Current State
        enum CONTROLLERSTATES state = SETUP;
    public:

        //Imma make these public so these can be set for testing
        double speed = MAX_VEL;
        double acceleration = MAX_ACC;

    //Constructor
        Controller(
            AccelStepper *pStepperL, 
            AccelStepper *pStepperR, 
            BMIHelper *pBMI, 
            struct PATHINFO *pPathInfo
        );

        void controllerInit();

        void controllerUpdate();

        // THESE SHOUlD BE GENERAL PURPOSE COMMANDS
        void turnTheta(double theta);
        void moveDistance(double distance);


        enum CONTROLLERSTATES getCurrentState();

        void startPath();

        void endPath();

}
#endif