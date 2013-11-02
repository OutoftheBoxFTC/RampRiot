/*
MotorOutput utilizes a scaled Velocity calculation. As such, when
MotorOutput reaches 100% (when the Heading is an odd multiple
of p/4) it will not have an effect. If the Omni-Drive has 4 motors as
in this example there is no real problem as the opposing MotorOutputs are at 0%.
In this example it is good practice to limit the rotation scalar to 30%
to allow the rate of turn to be approximately equal when traveling in
all directions
*/
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
