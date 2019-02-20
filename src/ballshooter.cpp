#include "ballshooter.h"
#include "hardware.h"
#include "drive.h"
#include "PIDController.h"
#include "main.h"
#include "pros/vision.h"

#define AUTO_AIM_SPEED .5
#define FLYWHEEL_ANGLE 60
#define FLYWHEEL_DIAMETER 4.0
#define LOW_FLAG_HEIGHT 18.3
#define MID_FLAG_HEIGHT 32.4
#define HIGH_FLAG_HEIGHT 46.3
#define FLYWHEEL_HEIGHT_FROM_GROUND 4.0

#define CLOSE_SHOT_CUTOFF_Y 100
#define FAR_SHOT_CUTOFF_Y 75

#define FLYWHEEL_INRANGE_RPM 100

using namespace pros;

bool fireBall(Color color, bool closeShot, bool farShot, bool isInAuto)
{
  if(autoAim(color))
    {
      vision_object out = Hardware::camera.get_by_sig(0, (color == red ? 2 : 1));
      bool isHighFlag = false;
      if((closeShot && out.y_middle_coord > CLOSE_SHOT_CUTOFF_Y) || (farShot && out.y_middle_coord > FAR_SHOT_CUTOFF_Y))
        isHighFlag = true;
      if(spinFlywheelToDistance(getDistanceToTarget(out.width * out.height), isHighFlag))
      {
        if(isInAuto)
          Hardware::intakeMotor.move_relative(1000, 127);
        else
          Hardware::intakeMotor.move(127);
      }
    }
  return false;
}

bool setFlywheelSpeed(int rpm)
{
  Hardware::flywheelPID.setTarget(rpm);
  Hardware::flywheelPID.pidOut = Hardware::flywheelPID.step();

  Hardware::leftFlywheelMotor.move_voltage(Hardware::flywheelPID.pidOut);
  Hardware::rightFlywheelMotor.move_voltage(Hardware::flywheelPID.pidOut);

  if(Hardware::flywheelPID.error < FLYWHEEL_INRANGE_RPM)
    return true;

  return false;
}


bool intakeBall(int direction)
{

  return false;
}

void spinUpFlywheel(int voltage){
  Hardware::leftFlywheelMotor.move_voltage(voltage);
  Hardware::rightFlywheelMotor.move_voltage(voltage);

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

  lcd::print(0, "x out: %i", out.x_middle_coord);

  if(out.x_middle_coord > 170)
    drive(AUTO_AIM_SPEED * 127, -AUTO_AIM_SPEED * 127);
  else if(out.x_middle_coord < 146)
    drive(-AUTO_AIM_SPEED * 127, AUTO_AIM_SPEED * 127);
  else
  {
    drive(0,0);
    return true;
  }

 return false;
}

#define SIZE_DISTANCE_SCALAR 1500.0//todo set me
//size to distance relationship is inverse linear.

float getDistanceToTarget(int area)
{
  return (SIZE_DISTANCE_SCALAR / area);
}

bool spinFlywheelToDistance(float inches, bool isHighFlag)
{
  float flagHeight = 0;
  if(isHighFlag)
    flagHeight = HIGH_FLAG_HEIGHT;
  else
    flagHeight = MID_FLAG_HEIGHT;

  float rpm = (720.0/(3.14159*FLYWHEEL_DIAMETER))
   * sqrt((-9.81 * inches) / ((flagHeight - FLYWHEEL_HEIGHT_FROM_GROUND
   - (inches * tan(FLYWHEEL_ANGLE))) * 2*pow(cos(FLYWHEEL_ANGLE),2)));

   return setFlywheelSpeed(rpm);
}
