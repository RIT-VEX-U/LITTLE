#include "ballshooter.h"
#include "hardware.h"
#include "PIDController.h"
#include "main.h"
bool fireBall(bool spinUpButton, bool fireButton, float distanceToFlag, float selected_flag_height)
{
  return false;
}

bool setFlywheelSpeed(int rpm)
{
  Hardware::flywheelPID.setTarget(rpm);
  Hardware::flywheelPID.pidOut = Hardware::flywheelPID.step();

  Hardware::leftFlywheelMotor.move_voltage(Hardware::flywheelPID.pidOut);
  Hardware::rightFlywheelMotor.move_voltage(Hardware::flywheelPID.pidOut);
  return false;
}


bool intakeBall(int direction)
{

  return false;
}

void spinUpFlywheel(int voltage){
  Hardware::leftFlywheelMotor.move_voltage(voltage);
  Hardware::rightFlywheelMotor.move_voltage(voltage);
  return;
}
