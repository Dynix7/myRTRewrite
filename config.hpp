#ifndef CONFIG_H
#define CONFIG_H

//DAC
#define VREF_VOLTAGE 0.9447
#define DAC_ADDRESS 0xD//0b00011011

#define STEPS_PER_REV 200*32 

//Screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIRE &Wire

//BMI270 IMU
#define IMU_ADDRESS 0x68
#define IMU_UPDATE_PERIOD 1.0/400 

//Robot physical dimensions
//in mm
#define WHEEL_RADIUS 40.6
#define TRACK_WIDTH 146.2
#define DIST_TO_DOWEL 85
#define RIGHT_OFF 1

//Kinematics

//in mm/s
#define MAX_ACC 500
#define MAX_VEL 2000

//in rad/sec
#define MAX_ANG_ACC 5 //5
#define MAX_ANG_VEL 10 //10

//Filter for angular velocity drift
#define COUNTER_BIAS 0.000008 // right bias 0.0001 left bias 0.0001
//BEST VALUE: 0.0003
//0 best value
//2.5*pow(10, -6)


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


// PINOUT GARBAGE
// CHANGE LATER

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
#define INDEX_L 47

//Right Motor
#define STEP_R 11
#define DIR_R 10
#define INDEX_R 12

#define STEP_EN 9


//SD Card
#define SD_CLK 38
#define SD_MISO 39
#define SD_MOSI 40
#define SD_CS 41



#endif
