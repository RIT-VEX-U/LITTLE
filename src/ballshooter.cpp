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

float PIDCalc(float targetVelocity){
  float flywheelVelocity = (Hardware::leftFlywheelMotor.get_actual_velocity() + Hardware::rightFlywheelMotor.get_actual_velocity()) / 2;
  float error = flywheelVelocity - targetVelocity;

  //float integral = iGain
}

void spinUpFlywheel(int voltage){
  Hardware::leftFlywheelMotor.move_voltage(-voltage);
  Hardware::rightFlywheelMotor.move_voltage(-voltage);
}
