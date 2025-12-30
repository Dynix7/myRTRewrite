#ifndef BMIHELPER_H
#define BMIHELPER_H

#include <SparkFun_BMI270_Arduino_Library.h>

class BMIHelper {
    private:

        BMI270 *imu = nullptr;

        double tickStart = 0.0;
        double deltaTime = 0.0;

        double dTheta = 0.0;
        double theta = 0.0;

        double gyroOffset = 0.0;

    public:

        // Constructor
        explicit BMIHelper(BMI270 *pIMU);

        // Functions (methods are a stupid name)
        void initGyro();
        void updateGyro();

        double getTheta();
        void resetTheta(); 

        //DEBUGGING dont use for operations
        double getdThetaDEBUG();
}       

#endif