#include "BMIHelper.hpp"
#include "misc.hpp"

#include <SparkFun_BMI270_Arduino_Library.h>


//Constructor
BMIHelper::BMIHelper(BMI270 *pIMU) : imu(pIMU) {
    if (imu == nullptr) {
        Serial.println("No IMU pointer given");
        return;
    }
}

void BMIHelper::initGyro() {

    delay(250);
    gyroOffset = 0.0;



        //Starts the BMI
    if (imu->beginI2C(IMU_ADDRESS) != BMI2_OK) {
        Serial.println("I2C or Wiring Error");
        return;
    }
    
    //Configuration profile
    bmi2_sens_config gyroConfig;

    gyroConfig.type = BMI2_GYRO;
    gyroConfig.cfg.gyr.odr = BMI2_GYR_ODR_400HZ;
    gyroConfig.cfg.gyr.range = BMI2_GYR_RANGE_500;
    gyroConfig.cfg.gyr.bwp = BMI2_GYR_OSR2_MODE;
    gyroConfig.cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
    gyroConfig.cfg.gyr.noise_perf = BMI2_PERF_OPT_MODE;

    if (imu->setConfig(gyroConfig) != BMI2_OK) {
        Serial.println("BMI configuration error");
    }


    //Automatic Calibration
    imu->performComponentRetrim();
    imu->performGyroOffsetCalibration();

    delay(250);


    //Manual Calibration

    //micros() is time from startup in microseconds
    int samples = 500;
    tickStart = toSec(micros());

    for (int i = 0; i < samples) {
        deltaTime = toSec(micros()) - tickStart; // Time since tick

        if (deltaTime >= IMU_UPDATE_PERIOD) {
            imu->getSensorData();
            tickStart = toSec(micros()); //Sets to current time

            gyroOffset += toRad(imu->data.gyroZ);
            
            i++;
        }
    }
    gyroOffset /= samples;
}


void BMIHelper::updateGyro() {
    deltaTime = toSec(micros()) - tickStart; //tickStart value from init or previous update

    if (deltaTime >= IMU_UPDATE_PERIOD) {
        imu->getSensorData();
        tickStart = toSec(micros());

        //Get and adjust Yaw with calculated offset
        dTheta = toRad(imu->data.gyroZ);
        dTheta = (dTheta - gyroOffset) * deltaTime; // radians/s, multiply by time to get radians

        theta += dTheta;
        theta = limitRad(theta);
    }

}

double BMIHelper::getTheta() {
    return theta;
}

void BMIHelper::resetTheta() {
    theta = 0.0;
}

// for debugging

double BMIHelper::getdThetaDEBUG() {
    return dTheta;
}