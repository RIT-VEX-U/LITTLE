#include "ballshooter.h"
#include "hardware.h"
bool fireBall(bool spinUpButton, bool fireButton, float distanceToFlag, float selected_flag_height)
{
  return false;
}


bool setFlywheelSpeed(int rpm)
{

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
