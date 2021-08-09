#include <Arduino.h>






// clibrate at the end
#define HOME_ANGLE 322

#define ANGLE_OFFSET 275

// set 1 to reverse
#define MOTOR_DIR 1
#define MOTOR_Port PORTF // F0 to F3

#define MAX_HEAD_WEIGHT 16.5 //g
// #define MAX_HEAD_WEIGHT 4 //g

//
#define HOME_PIN 23

// must be int
#define ENCODER_A_PIN 19  
#define ENCODER_B_PIN 18
#define ENCODER_PER_REV 2000

#define BUZZER_PIN 8

// #define PITCH_DEV_LIMIT 20
// #define ROLL_DEV_LIMIT 20

#define DEG_TO_RAD 0.017453292519943295769236907684886

#define NO_GCODE_COMMANDS 10


// 94.2477 * 0.176 / 360
#define X_PER_UNIT 0.0460 //mm

#define ANGLE_PER_STEP 0.176

#define MAX_X_LENGTH 70

#define KP 10
#define KD 100
#define KI 0

// #define KP 0.0184
// #define KD 0.4
// #define KI 0
