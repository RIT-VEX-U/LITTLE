#include "main.h"
#include "hardware.h"
#include "ballshooter.h"
#include "drive.h"
#include "PIDController.h"

using namespace pros;

void opcontrol()
{

	while(true)
	{
		//Driving Control
		driveTank(Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), false);
		//End Driving Control

		//Operating Controls
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L1))
      Hardware::flipperMotor.move_voltage(6000);
    else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L2))
      Hardware::flipperMotor.move_voltage(-6000);
    else
      Hardware::flipperMotor.move_voltage(0);


    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R2)){
      Hardware::intakeMotor.move_voltage(-12000);
    }else{
      Hardware::intakeMotor.move_voltage(0);
    }

    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_A))
      autoAim(red);

    /*
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_UP)){
      Hardware::flywheelPID.setTarget(4000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_RIGHT)){
      Hardware::flywheelPID.setTarget(3000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_LEFT)){
      Hardware::flywheelPID.setTarget(2000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
      Hardware::flywheelPID.setTarget(0);
    }
    */

		//End Operating Controls


    /*lcd::print(0, "Left: %f", Hardware::leftFlywheelMotor.get_actual_velocity());
    lcd::print(1, "Right: %f", Hardware::rightFlywheelMotor.get_actual_velocity());
    lcd::print(2, "Target RPM: %f", Hardware::flywheelPID.target);
    lcd::print(3,"cumError: %f", Hardware::flywheelPID.cumError);
    lcd::print(4, "PID Out: %f, Error: %f", Hardware::flywheelPID.pidOut, Hardware::flywheelPID.error);
    lcd::print(5, "Controller Speed Read: %f", Hardware::flywheelPID.victims[0]->get_actual_velocity() * 35);
    */
    /*lcd::print(6, "pComp: %f, iComp: %f, dComp: %f",
    Hardware::flywheelPID.pGain * Hardware::flywheelPID.error,
    Hardware::flywheelPID.iGain * Hardware::flywheelPID.cumError,
    Hardware::flywheelPID.dGain * Hardware::flywheelPID.dError);*/


    delay(20);
	}
}
