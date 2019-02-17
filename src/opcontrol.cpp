#include "main.h"
#include "hardware.h"
#include "ballshooter.h"
#include "drive.h"
#include "PIDController.h"

using namespace pros;

void opcontrol()
{
  float setVelocity = 0;
  float pidOut = 0;
  PIDController flywheelPID = PIDController(1,1,1,20,Hardware::leftFlywheelMotor);
	while(true)
	{
		//Driving Control
		driveTank(Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), Hardware::controller1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y), false);
		//End Driving Control

		//Operating Controls
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L1)){
      Hardware::flipperMotor.move_voltage(6000);
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_L2)){
      Hardware::flipperMotor.move_voltage(-6000);
    }else{
      Hardware::flipperMotor.move_voltage(0);
    }

    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_UP)){
      setVelocity += 100;
      if(setVelocity > 7000)
        setVelocity = 7000;
    }else if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_DOWN)){
      setVelocity -= 100;
      if(setVelocity < 0){
        setVelocity = 0;
      }
    }

    /*
    if(Hardware::controller1.get_digital(E_CONTROLLER_DIGITAL_R1)){
        spinUpFlywheel(12000);
    }else{
      spinUpFlywheel(0);
    }
    */

		//End Operating Controls
    flywheelPID.setTarget(setVelocity);
    pidOut = flywheelPID.step();
    Hardware::leftFlywheelMotor.move_voltage(pidOut);
    Hardware::rightFlywheelMotor.move_voltage(pidOut);

    lcd::print(0, "Left: %f", Hardware::leftFlywheelMotor.get_actual_velocity());
    lcd::print(1, "Right: %f", Hardware::rightFlywheelMotor.get_actual_velocity());
    lcd::print(2, "Target RPM: %f", flywheelPID.target);
    lcd::print(3,"cumError: %f", flywheelPID.cumError);
    lcd::print(4, "PID Out: %f, Error: %f", pidOut, flywheelPID.error);
    lcd::print(5, "Controller Speed Read: %f", flywheelPID.victim->get_actual_velocity());
    lcd::print(6, "pComp: %f, iComp: %f, dComp: %f",
    flywheelPID.pGain * flywheelPID.error,
    flywheelPID.iGain * flywheelPID.cumError,
    flywheelPID.dGain * flywheelPID.dError);


    delay(20);
	}
}
