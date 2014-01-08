#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTIRS2,         sensorNone)
#pragma config(Sensor, S3,     HTMC,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     Motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Motor5,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Motor6,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

task main()
{
	motor[Motor5] = -50;  // Makes it go downs with positives
	motor[Motor6] = -50;  // Makes it go downs with positives
	while(true);
}
