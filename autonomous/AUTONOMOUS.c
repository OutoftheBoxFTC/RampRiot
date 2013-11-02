#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     USonic,         sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     Motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     Motor5,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motor6,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma platform(Tetrix)
//Include Dependiences
#include "JoystickDriver.c"
#include "\Projects\RampRiot\autonomous\AUTONOMOUS_P1.h"
#include "\Programs\IR_APIS\10_28_13_V1.1_Holonomic_.c"
#include

task main()
{
	StartTask(p1);
}
