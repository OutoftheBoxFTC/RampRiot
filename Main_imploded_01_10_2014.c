#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTMC,           sensorI2CCustom)
#pragma config(Sensor, S4,     HTIRS2,         sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     Motor1,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Motor2,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Motor3,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Motor4,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     Motor5,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     Motor6,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(Tetrix)

//Joystick API //
#include "JoystickDriver.c"

//Drive API //
/*
MotorOutput utilizes a scaled Velocity calculation. As such, when
MotorOutput reaches 100% (when the Heading is an odd multiple
of p/4) it will not have an effect. If the Omni-Drive has 4 motors as
in this example there is no real problem as the opposing MotorOutputs are at 0%.
In this example it is good practice to limit the rotation scalar to 30%
to allow the rate of turn to be approximately equal when traveling in
all directions
*/

//Holo API//
typedef enum {//List of directions our robot can go
	forward,
	reverse,
	left,
	right,
	spin_left,
	spin_right,
	diagonal_F_L,// Diagnal format is = diagonal_vertical_horizontal
	diagonal_F_R,// Diagnal format is = diagonal_vertical_horizontal
	diagonal_R_R,// Diagnal format is = diagonal_vertical_horizontal
	diagonal_R_L,// Diagnal format is = diagonal_vertical_horizontal
	none
} Direction;

//Set the speed of the omni-drive robot.
void control(int m1, int m2, int m3, int m4) {
	motor[Motor1] = m1;//asignment to motor1's speed
	motor[Motor2] = m2;//asignment to motor2's speed
	motor[Motor3] = m3;//asignment to motor3's speed
	motor[Motor4] = m4;//asignment to motor4's speed
}

void move(Direction dir, int power) { //move function
	switch(dir) {//switch through all Direction values
		case forward: //check if case of dir equals forward
			control(-1 * power, power, power, -1 * power);//assigns power to robot based off case
			break;
	  case reverse: //check if case of dir equals reverse
			control(power, -1 * power, -1 * power, power);//assigns power to robot based off case
			break;
	  case left: //check if case of dir equals left
			control(power, power, -1 * power, -1 * power);//assigns power to robot based off case
			break;
		case right: //check if case of dir equals right
			control(-1 * power, -1 * power, power, power);//assigns power to robot based off case
			break;
	  case spin_left: //check if case of dir equals spins_left
			control(power, power, power, power);//assigns power to robot based off case
			break;
		case spin_right: //check if case of dir equals spins_left
			control(-1 * power, -1 * power, -1 * power, -1 * power);//assigns power to robot based off case
			break;
	  case diagonal_F_L: //check if case of dir equals diagonal_F_L
			control(0, power, 0, -1 * power);//assigns power to robot based off case
			break;
	  case diagonal_F_R: //check if case of dir equals diagonal_F_R
			control(-1 * power, 0, power, 0);//assigns power to robot based off case
			break;
		case diagonal_R_R: //check if case of dir equals diagonal_R_R
			control(0, -1 * power, 0, power);//assigns power to robot based off case
			break;
	  case diagonal_R_L: //check if case of dir equals diagonal_R_L
			control(power, 0, -1 * power, 0);//assigns power to robot based off case
			break;
	  default:
	  	control(0, 0, 0, 0);
		};
}



float getMotorOutput(float velocity, int direction, float motorOffset)
{
	float output = velocity * sinDegrees(round(direction - motorOffset));
	//nxtDisplayTextLine(6, "output - %d", output); - Debugging
	return output;

}

int getDirectionFromLocation(int x, int y)
{
	//Calculates the Direction using Arc Tangent Angle 2 and returns a value 0-360
	//float direction = atan2(joystick.joy1_y1 + 1,joystick.joy1_x1) / PI * 180; - This works but goes 0-180 and not 0-360
	//float direction = atan2(joystick.joy1_y1 + 1,joystick.joy1_x1) / PI * 180 + 180; - This goes 0-360 but is counter clockwise
	int direction = (atan2(y + 1, x) / PI * 180 * -1 + 180);// Works perfectly and resolves previous problems

	//Rotates the degrees 90 to the right. Resulting in the top point being 0
	if(direction < 90)
	{
		direction += 270;
	} else
	{
		direction -= 90;
	}
	return direction;
}


// I don't know why these are not defined in joystickdriver.c or something.
// The TJoystick structure includes a buttons field that is a bit map of any
// and all buttons that are currently pressed. Button 1 sets bit 1 and so on.
#define button1   0x01
#define button2   0x02
#define button3   0x04
#define button4   0x08
#define button5   0x10
#define button6   0x20
#define button7   0x40
#define button8   0x80
#define button9  0x100
#define button10 0x200

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
  servo[servo1] = 215;
  servo[servo2] = 40;
  servo[servo3] = 0;
  servo[servo4] = 0;
  servo[servo5] = 0;
  return;
}

/*
Checks if the joystick is being currently controlled or moved to prevent
constant actions of being ran when in a 0 0 position.
*/
bool isJoystickBeingMoved(int axis)
{
	//Is the axis of between 10 and -10
	return (axis <= 10 && axis >= -10);
}

/*
Converts the Y Mapping of the Joystick to a speed from 0-100
*/
int getVelocityFromJoy2()
{
        int more_power;
	//0, 0  on the joystick corilates to a power of 50
	//Top = 100
	//Bottom = 100

        if((((joystick.joy1_y2 + 128) * 100) / 256) < 30)
        {
        more_power=30;
        }
        else
        {
        more_power=((joystick.joy1_y2 + 128) * 100) / 256;
        }

	return (more_power);
}

/*
Combines all functions in the Library to set the robots motors
power to head in a direction.
*/
void assignMotorSpeedFromJoyStick()
{
	//Get the direction in degrees that the robot needs to head from a coordinate map
	int direction = getDirectionFromLocation(joystick.joy1_x1, joystick.joy1_y1);
	//Gets the velocity/speed from Joystick 2
	float velocity = getVelocityFromJoy2();
	float defaultOffset = 45;

	//Default motor speeds are 0 if the robots are at joystick 1 at 0 , 0
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;
	//If the joysticks are NOT at 0,0 calculate the power of the motors
	//This is required because function sin returns 70 when the joystick is at 0,0
	if(!isJoystickBeingMoved(joystick.joy1_x1) || !isJoystickBeingMoved(joystick.joy1_y1))
	{
		//The joystick is not at 0,0 so we update the power
		m1 = getMotorOutput(velocity, direction, 1 * defaultOffset);
		m2 = getMotorOutput(velocity, direction, 3 * defaultOffset);
		m3 = getMotorOutput(velocity, direction, 5 * defaultOffset);
		m4 = getMotorOutput(velocity, direction, 7 * defaultOffset);
			//Apply new power
	}
	control(m1, m2, m3, m4);
	// Debugging
	/*nxtDisplayTextLine(0, "m1 - %d", m1);
	nxtDisplayTextLine(1, "m2 - %d", m2);
	nxtDisplayTextLine(2, "m3 - %d", m3);
	nxtDisplayTextLine(3, "m4 - %d", m4);
	nxtDisplayTextLine(4, "Direction - %d", direction);*/
}

void rotateRobot()
{

	if (joystick.joy1_Buttons & button5)
	{
		move(spin_left, getVelocityFromJoy2());
	} else if (joystick.joy1_Buttons & button6)
	{
		move(spin_right, getVelocityFromJoy2());
	}
}



task main()
{
        bool useCompass = true;
	//HTMCsetTarget(HTMC, 180);
	waitForStart();
	eraseDisplay();
	initializeRobot();

  waitForStart();   // wait for start of tele-op phase

	while (true)
	{


      /* OLD CODE
        if (joystick.joy1_Buttons & button5)
		{
			move(spin_right, getVelocityFromJoy2());
		} else if (joystick.joy1_Buttons & button6)
		{
			move(spin_left, getVelocityFromJoy2());
		} else
  	{
			assignMotorSpeedFromJoyStick();
		}

		if (joystick.joy2_Buttons & button4)
		{
			servo[servo7] = 100;
			servo[servo8] = 146;
		} else if (joystick.joy2_Buttons & button3)
		{
			servo[servo7] = 185;
			servo[servo8] = 59;
		} else if (joystick.joy2_Buttons & button2)
		{
			servo[servo7] = 217;
			servo[servo8] = 30;
		} else if (joystick.joy2_Buttons & button1)
		{
			servo[servo7] = 40;
			servo[servo8] = 212;
		}

	  if (joystick.joy2_Buttons & button5)
		{
			motor[motor6] = 30;
				motor[motor5] = 30;
		} else if (joystick.joy2_Buttons & button7)
	  {
	  	motor[motor6] = -30;
	  		motor[motor5] = -30;
	  } else
	  {
	  	motor[motor6] = 0;
	  		motor[motor5] = 0;
	  } */


          if(joystick.joy2_Buttons & button5)
		{
			motor[motorJ] = 60;
			//motor[MotorK] = 100;  //BUCKET UP
		}
		else if(joystick.joy2_Buttons & button6)
		{
			motor[motorJ] = -60;
			//	motor[MotorK] = -100; //BUCKET UP
		}
		else
		{
			motor[motorJ] = -0;  //STOP MOVE
			//	motor[MotorK] = -0;s
		}

		if(joystick.joy2_Buttons & button2)
		{  // dump blocks procedure (A BUTTON)
			servo[servo3] = 255;
			wait10Msec(20);
			servo[servo1] = 65;
			servo[servo2] = 190;
		}

		else if(joystick.joy2_Buttons & button3)
		{  // PICKUP position (B BUTTON)
			servo[servo3] = 255;
			wait10Msec(20);
			servo[servo1] = 100;
			servo[servo2] = 155;
		}
		else if(joystick.joy2_Buttons & button4)
		{  // HOLD POSITION (Y BUTTON)
			servo[servo3] = 150;
			wait10Msec(20);
			servo[servo1] = 200;
			servo[servo2] = 55;
		}

		else if(joystick.joy2_Buttons & button1)
		{  // MOVE KITTY ARM (X BUTTON)
		servo[servo3] = (servo[servo3] > 125 ? 0 : 255);
			//		wait10Msec(20);
			//		servo[servo1] = 155;
			//		servo[servo2] = 110;
		}

    if(joystick.joy1_Buttons & button5)
		{
			move(spin_right, getVelocityFromJoy2());  //SPIN
		}
		else if(joystick.joy1_Buttons & button6)
		{
			move(spin_left, getVelocityFromJoy2());  //SPIN
		}
		else
		{
			assignMotorSpeedFromJoyStick();
		}


                if(joystick.joy1_Buttons & button7)
		{
			motor[Motor5] = 100;
			motor[Motor6] = 100;
		}
		else if(joystick.joy1_Buttons & button8)
		{
			motor[Motor5] = -100;
			motor[Motor6] = -100;
		}
		else if(joystick.joy1_Buttons & button4)
		{
			motor[Motor5] = 0;
			motor[Motor6] = 0;
		}

		/*if(joystick.joy1_Buttons & button1)
		{   //SET TARGET
			int val;
			move (spin_left, 25);
			while (true)
			{
				val = HTMCreadHeading(HTMC);
				nxtDisplayString(1, "%d", val);
				nxtDisplayString(2, "%d", getDirection(read() + 40));
				nxtDisplayString(3, "%d", getDirection(read() - 40));
				if (val <= getDirection(read() + 20) && val >= getDirection(read() - 20)) {
					break;
				}
			}
			move (none, 0);
			wait10Msec(20);
			HTMCsetTarget(HTMC);
			PlaySound(soundBeepBeep);
			wait1Msec(100);
		}
		else if(joystick.joy1_Buttons & button2)
		{  //SWITCH BTWEEN COMPASS AND NO COMPASS
			useCompass = !useCompass;
			if(useCompass)
			{
				PlaySound(soundBlip);
				PlaySound(soundBlip);
				PlaySound(soundBlip);
			}
			else
			{
				PlaySound(soundFastUpwardTones);
			}
			wait10Msec(75);
		}*/
		if(joystick.joy2_TopHat == 0)
		{
			if(servo(servo4) > 10)
			{
				motor[motorK] = 90;  //IF SERVO IS OUT SPIN
			}
			else
			{
				motor[motorK] = 0;  //NO SPIN
			}
		}
		else if(joystick.joy2_TopHat == 4)
		{
			if((servo[servo4] > 10))
			{
				motor[motorK] = 50; //SPIN SLOW
			}
			else                  // Q Look he has a bandana so stylish
			{
				motor[motorK] = 0;  //NO SPIN
			}
		}
		else
		{
			motor[motorK] = 0;  //NO SPIN
		}

		if(joystick.joy2_TopHat == 2)
		{
			servo[servo4] = 60;  // MOVE SERVO OUT
		}
		else if(joystick.joy2_TopHat == 6)
		{
			servo[servo4] = 0;  // MOVE SERVO IN
		}

		if(joystick.joy1_Buttons & button7)
		{
			motor[Motor5] = 100;   //HANG BARS UP
			motor[Motor6] = 100;
		}
		else if(joystick.joy1_Buttons & button8)
		{
			motor[Motor5] = -100;  //HANG BARS DOWN
			motor[Motor6] = -100;
		}
		else if(joystick.joy1_Buttons & button4)
		{
			motor[Motor5] = 0;  // STOP MOVE
			motor[Motor6] = 0;
		}

                /*
		if(joystick.joy2_Buttons & button7)
		{
			motor[Motor5] = 100;   // SAME FROM LAST ON DIFF CONTROL
			motor[Motor6] = 100;
		}
		else if(joystick.joy2_Buttons & button8)
		{
			motor[Motor5] = -100;
			motor[Motor6] = -100;
		}  Used to Override JOY1... Not a good
		*/

		if(joystick.joy1_Buttons & button3)
		{
			servo[servo5] = 0;  // DEPOSIT BLOC IF STILL IN
		}
		else
		{
			servo[servo5] = 255; // PULL ARM BACK
		}

	  getJoystickSettings(joystick);
	}
}
