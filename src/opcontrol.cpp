#include "main.h"
#include "external_functions.h"
#include "hardware.h"


using namespace pros;


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
		driveTank(Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), false);

		//End Driving Control

		//Operating Controls
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R1)){
      Hardware::leftFlywheelMotor.move(127);
      Hardware::rightFlywheelMotor.move(127);
    }
    else{
      Hardware::leftFlywheelMotor.move(0);
      Hardware::rightFlywheelMotor.move(0);
    }
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R2)){
      Hardware::intakeMotor.move(127);
    }
    else{
      Hardware::intakeMotor.move(0);
    }
		//End Operating Controls


	}
}
