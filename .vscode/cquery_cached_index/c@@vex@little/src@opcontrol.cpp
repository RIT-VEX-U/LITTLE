#include "main.h"
#include "hardware.h"
#include "ballshooter.h"
#include "drive.h"

using namespace pros;

// Drive to distance given
void driveDist(int inch){
  while(Hardware::frontLeftMotor.get_position()*SPROCKET_ROTATION < inch){
    drive(100, 100); //lowered speed for more accuracy
  }
  drive(-20, -20); //quick brake if needed
  delay(500);
  drive(0, 0);
}

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
        spinUpFlywheel(12000);
    }else{
      spinUpFlywheel(0);
    }

    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L1)){
      Hardware::flipperMotor.move_voltage(6000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L2)){
      Hardware::flipperMotor.move_voltage(-6000);
    }else{
      Hardware::flipperMotor.move_voltage(0);
    }
		//End Operating Controls


	}
}
