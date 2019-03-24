#include "ballshooter.h"
#include "hardware.h"
#include "drive.h"
#include "PIDController.h"
#include "main.h"
#include "pros/vision.h"

#define AUTO_AIM_SPEED .4
#define FLYWHEEL_ANGLE 60.0
#define FLYWHEEL_DIAMETER 4.0
#define LOW_FLAG_HEIGHT (18.3/12.0
#define MID_FLAG_HEIGHT (32.4/12.0)
#define HIGH_FLAG_HEIGHT (46.3/12.0)
#define FLYWHEEL_HEIGHT_FROM_GROUND (4.0/12.0)
#define AUTOAIM_DISTANCE_DEADBAND (2/12.0)//feet

#define HIGH_FLAG_CUTOFF

#define CLOSE_SHOT_CUTOFF_Y 30
#define FAR_SHOT_CUTOFF_Y 40

#define FLYWHEEL_INRANGE_RPM 200

using namespace pros;

/**
  Fires the ball by first checking whether we are lined up, then getting
  and spinning up the flywheel motor based on how far away from the flag the
  bot is, and when it is at speed, running the intake to feed a ball into the
  flywheel.

  Will look for the flag of the color input.
  If closeShot is selected, then it will automatically choose which flag it is
  looking at based on the "cutoff angle", same for a far shot. This is to make
  sure the getDistance function works properly and sets the right RPM for the
  flag height.

  If isInAuto is selected, then it runs the intake for a set time.

  Returns true if we have shot a ball, or are in the process of firing a ball.
*/
bool fireBall(Hardware::Color color, bool highShot, bool midShot, bool isInAuto)
{
  if(!highShot && !midShot)
    return false;

  if(autoAim(color) && autoAimDistance(Hardware::ult1.get_value(), highShot))
    {
      drive(0,0);
      if(setFlywheelSpeed(7000))
      {
        if(isInAuto)
          Hardware::intakeMotor.move_relative(-900*10, 127);
        else
          Hardware::intakeMotor.move(-127);
        return true;
      }
    }
  return false;
}

/**
  Inputs into the PID loop the RPM we want.

  Returns true if the current RPM of the flywheel is within a certain range.
*/
bool setFlywheelSpeed(int rpm)
{
  Hardware::flywheelPID.setTarget(rpm);

  if(abs(Hardware::flywheelPID.velocity) > (rpm - FLYWHEEL_INRANGE_RPM))
    return true;

  return false;
}

/**
  Simply "primes" the flywheel to a certain voltage to avoid the delay of
  spinning up before firing. Not for actual firing use, as there is no
  velocity feedback.
*/
void spinUpFlywheel(int voltage){
  Hardware::leftFlywheelMotor.move_voltage(voltage);
  Hardware::rightFlywheelMotor.move_voltage(voltage);

}

/**
  Uses a "bang-bang" feedback control to automatically aim the bot at the flag.
  This is done by comparing X value of the largest blob of that color to the
  center of the camera, and controlling whether the robot turns left or right.
*/
bool autoAim(Hardware::Color color)
{
  pros::vision_object out;
  if(color == Hardware::Color::blue)
  {
  out = Hardware::camera.get_by_sig(0, 1);
}else if(color == Hardware::Color::red)
  {
  out = Hardware::camera.get_by_sig(0, 2);
  }

  //lcd::print(0, "x out: %i", out.x_middle_coord);

  if(out.x_middle_coord > 158+10)
    drive(AUTO_AIM_SPEED * 127, -AUTO_AIM_SPEED * 127);
  else if(out.x_middle_coord < 158-10)
    drive(-AUTO_AIM_SPEED * 127, AUTO_AIM_SPEED * 127);
  else
  {
    drive(0,0);
    return true;
  }

 return false;
}

/**
  Automatically sets the robot distance away from the wall behind the flag,
  and uses the ultrasonic sensor to drive to it.

  Originally this method used the camera to detect the height of the flag and
  use trig to calculate the distance away from it. It worked, but only if one
  flag was present at a time, because figuring out which flag is which without
  context is difficult.
*/
bool autoAimDistance(float ultVal, bool isHighFlag)
{
  //float targetDist = ((isHighFlag ? HIGH_FLAG_HEIGHT : MID_FLAG_HEIGHT) / tan((3.14159 / 180.0) * FLYWHEEL_ANGLE))+1;
  float targetDist = (isHighFlag ? 3 : 1.5);
  float currentDist = ultVal / (2.54*12*10);
  //lcd::print(0, "target: %f, current: %f", targetDist, currentDist);
  if(fabs(currentDist - targetDist) < AUTOAIM_DISTANCE_DEADBAND)
  {
    drive(0,0);
    return true;
  }else if(currentDist < targetDist)
    drive(-AUTO_AIM_SPEED * 127, -AUTO_AIM_SPEED * 127);
  else if(currentDist > targetDist)
    drive(AUTO_AIM_SPEED * 127, AUTO_AIM_SPEED * 127);

  return false;
}

/**
  Gets the distance across the ground to the flag pole, in feet,
  given the Y coordinate from the camera and whether the current
  flag is the high flag or the low flag.

  This uses a basic tanx = opposite / adjacent, or rather
  tan(cameraAngle) = flagHeight / distanceToFlag. Simplified it's:
  distanceToFlag = flagHeight / tan(cameraAngle)
*/
float getDistanceToTarget(int y, bool isHighFlag)
{
  return (isHighFlag ? HIGH_FLAG_HEIGHT : MID_FLAG_HEIGHT) / tan((3.14159 / 180.0) * (212 - y) * (45.0/212.0));
}

/**
  Sets the flywheel speed based on the distance from the flag, in feet.
  This was calculated using physics ballistics equations, and an equation
  to turn RPM to tangential velocity on the ball.
  This also requires that we know the height of the flag, and therefore which
  flag we are looking at.

  returns true if we are within a deadband of the RPM
*/
bool spinFlywheelToDistance(float feet, bool isHighFlag)
{
  float flagHeight = 0;
  if(isHighFlag)
    flagHeight = HIGH_FLAG_HEIGHT;
  else
    flagHeight = MID_FLAG_HEIGHT;

  float rpm = (720.0/(3.14159*FLYWHEEL_DIAMETER))
   * sqrt((-9.81 * pow(feet,2)) / ((flagHeight - FLYWHEEL_HEIGHT_FROM_GROUND
   - (feet * tan((3.14159/180.0) * FLYWHEEL_ANGLE))) * 2*pow(cos((3.14159/180.0) * FLYWHEEL_ANGLE),2)));

   lcd::print(1, "RPM: %f", rpm);

   return setFlywheelSpeed(rpm);
}
