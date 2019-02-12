#include "main.h"
#include "hardware.h"

using namespace pros;


//==================== DRIVING CODE ====================
/**
 *	Drives the robot using a tank-system.
 *
 *	Squaring the inputs allows slower control over the majority of the
 *	joystick band, but still allows fast movements near the end, following
 		a x^2 curve. Leave as false for a y=x linear function.
 */
void drive(float left, float right, bool square_inputs)
{

float left_out = left / 127.0;
float right_out = right / 127.0;

int left_sign = (left_out > 0) ? 1 : (left_out < 0) ? -1 : 0;
int right_sign = (right_out > 0) ? 1 : (right_out < 0) ? -1 : 0;

if(square_inputs)
{
	left_out = pow(left_out, 2) * left_sign;
	right_out = pow(right_out, 2) * right_sign;
}

frontLeftMotor.move(left_out * 127);
backLeftMotor.move(left_out * 127);
frontRightMotor.move(right_out * 127);
backRightMotor.move(right_out * 127);
}
//================== END DRIVING CODE ===================

//====================OPERATING CODE=====================

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
 	{


	while(true)
	{
		//Driving Control
		drive(controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), true);

		//End Driving Control

		//Operating Controls

		//End Operating Controls


	}
	}
