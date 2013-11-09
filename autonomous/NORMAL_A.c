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
#include "\Programs\RampRiot\autonomous\AUTONOMOUS_P1.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//                            Autonomous Setup and Control
// Choose an autonomous file from the incuded files and executes it. Additionally It resets all
// motors to default positions and creates a infinite loop
//
///////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	servo[servo1] = 0;
	servo[servo2] = 0;
	servo[servo3] = 255;
	//Wait till start too begin executing
	waitForStart();
	//Reset The servers to the default rotation

	//       DELETE ME          //
	//wait10Msec(1500);         //DELETE ME
	//       DELETE ME          //

	//Start an autonomous program from the incuded files.
	StartTask(p1);

	//Start a paging file to act as a program place holder.
	while (true) {
		wait10Msec(1);
	}
}
