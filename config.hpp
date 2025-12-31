#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoEigenDense.h>
using namespace Eigen;


//DAC
#define VREF_VOLTAGE 0.9447
#define DAC_ADDRESS 0x0D 
//0b0001101, Depends on the wiring on the ADR0 pin,
// This is if its connected to GND
//MAKE SURE TO WRITE ONE MORE BIT FOR WRITE

#define STEPS_PER_REV (200*32) 

//Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIRE &Wire

//BMI270 IMU
#define IMU_ADDRESS 0x68
#define IMU_UPDATE_PERIOD 1.0/400 //400Hz

//Robot physical dimensions
//in mm
#define WHEEL_RADIUS 40.6
#define TRACK_WIDTH 146.2
#define DIST_TO_DOWEL 85

//Kinematics

//in mm/s
#define MAX_ACC 500
#define MAX_VEL 2000

//in rad/sec
#define MAX_ANG_ACC 5   
#define MAX_ANG_VEL 10 // might reduce to 8.5 since the bmi config I set the max to 8.72


//PATH INFO
#define PATH_FILE "/path.txt" 
#define LOG_FILE "/log.txt"

//STATE DEFINITIONS i love enums

enum RTSTATES{
    INIT = -1,
    IDLE,  
    READY, 
    RUNNING,
    END_RUN,
    STOPPED,
    ADJUST_MENU,
    ADJUST_X,
    ADJUST_Y,
    ADJUST_TIME,
    TESTING_TURNS,
    VERBOSE 
};

enum CONTROLLERSTATES {
    SETUP, //0
    SETMOVE,
    SETTURN,
    MOVEMENT,
    TURNING,
    FINISHMOVE, // Currently doesn't do anything though might in future
    FINISHTURN,
    END

};

// im gonna keep the follow mode at 1 for the sake of cross compatibility
// It shouldn't matter since the names should always be used over the number
enum PATHMODE {
    FOLLOW = 1, //1
    TESTING // 2
};


// Struct for the path info
struct PATHINFO {
    Vector2f PATH[80] = {0};
    enum PATHMODE mode;
    double targetTime = 0.0;
    int currentIndex = 0;
    int targetIndex = 1;
    int lastIndex = 0;

};




// PINOUT GARBAGE
// CHANGE LATER


// ATTENTION SO BASICALLY DEPENDING ON THE WIRING THE SPREAD MIGHT BE HARDCODED
// SO LIKE THIS WOULD DO NOTHING SO LIKE CHECK THE PCB DESIGN FOR THAT
// LIKE IT WOULD PROBABLY BE EASIER JUST TO ALWAYS BE PULLED TO HIGH FOR SPREADCYCLE
#define SPREAD 45



//I2C PINS

#define SDA_PIN 17
#define SCL_PIN 18

//Buttons for input(
#define BTN_0 2 //INIT | x
#define BTN_1 1 //RUN | TIME ADJUST
#define BTN_2 3 //ADJUSTMENTS | X ADJUST
#define BTN_3 4 //LASERS | Y ADJUST

//Rotary Encoder
#define INCR_BTN 5
#define INCR_A 15
#define INCR_B 16

//Indicatiors
#define BUZZER 8
#define LED_0 6
#define LED_1 7

//Left Motor
#define STEP_L 21
#define DIR_L 14


//Right Motor
#define STEP_R 11
#define DIR_R 10


#define STEP_EN 9


//SD Card
#define SD_CLK 38
#define SD_MISO 39
#define SD_MOSI 40
#define SD_CS 41



#endif
