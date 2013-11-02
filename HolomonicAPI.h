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
