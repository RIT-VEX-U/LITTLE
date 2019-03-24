#include "main.h"
#include "hardware.h"
#include "ballshooter.h"
#include "drive.h"
#include "PIDController.h"
#include "initialize.h"

using namespace pros;

void opcontrol()
{

	while(true)
	{
		//Driving Control
    if(!Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_A))
		  driveTank(Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), false);
		//End Driving Control

		//Operating Controls
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
      Hardware::flipperMotor.move_voltage(6000);
    else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L2))
      Hardware::flipperMotor.move_voltage(-6000);
    else
      Hardware::flipperMotor.move_voltage(0);


    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R2))
      Hardware::intakeMotor.move_voltage(-12000);
		else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R1))
			Hardware::intakeMotor.move_voltage(12000);
		else
      Hardware::intakeMotor.move_voltage(0);


		fireBall(Initialize::flagColor, Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_A),
		 Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_B), false);

		 lcd::print(1, "gyro: %f", Hardware::gyro.get());

		 //if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_A))
		 	//autoAim(Initialize::currentColor);

    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_UP)){
      Hardware::flywheelPID.setTarget(7000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
      Hardware::flywheelPID.setTarget(3000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
      Hardware::flywheelPID.setTarget(2000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
      Hardware::flywheelPID.setTarget(0);
    }


		//End Operating Controls



    delay(20);
	}
}
