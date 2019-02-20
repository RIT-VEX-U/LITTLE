#include "ballshooter.h"
#include "hardware.h"
#include "PIDController.h"
#include "main.h"

#define AUTO_AIM_SPEED .2

pros::vision_signature blue_signature = pros::Vision::signature_from_utility(1, -3817, -3307, -3562, 12179, 13435, 12807, 8.8, 0);//BLUE
pros::vision_signature red_signature = pros::Vision::signature_from_utility(2, 8595, 8905, 8750, -717, -353, -535, 8.8, 0);//RED

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

bool autoAim(Color color)
{
  pros::vision_object out;
  if(color == blue)
  {
  out = Hardware::camera.get_by_sig(0, 1);
  }else if(color == red)
  {
  out = Hardware::camera.get_by_sig(0, 2);
  }

  pros::lcd::print(0, "x out: %i", out.x_middle_coord);
 return false;
}
