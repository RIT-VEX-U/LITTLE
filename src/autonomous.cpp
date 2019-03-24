#include "main.h"
#include "hardware.h"
#include "drive.h"
#include "initialize.h"
#include "ballshooter.h"


enum AutoPath
{
  init, driveToFireDist1, fireBall1, backUpToInitialPos1, turnToGetBall,
   driveToBall, pickupBall, backUpToInitialPos2, turnToFlag, driveToFireDist2,
   fireBall2, end
};


AutoPath currentPosition = init;

int savedLeftEncoder = 0;
int savedRightEncoder = 0;

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  while(true)
  {
  switch(currentPosition)
  {
    case init:
      currentPosition = driveToFireDist1;
    break;
    case driveToFireDist1:
      if(driveInches(24.0, .5))
      {
        currentPosition = fireBall1;
        resetEncoders();
      }
    break;
    case fireBall1:
      if(fireBall(Initialize::flagColor, true, false, true))
      {
        pros::delay(5000);
        Hardware::flywheelPID.setTarget(0);
        Hardware::leftMotor.move_absolute(0, .4 * 127);
        Hardware::rightMotor.move_absolute(0, .4 * 127);
        pros::delay(1000);
        currentPosition = backUpToInitialPos1;
      }
    break;
    case backUpToInitialPos1:
      if(driveInches(33, -.5))
        currentPosition = turnToGetBall;
    break;
    case turnToGetBall:
      if(turnDegrees((Initialize::currentColor == Hardware::Color::red ? 1 : -1) * 90, .5))
        currentPosition = driveToBall;
    break;
    case driveToBall:
      if(driveInches(24 + 3, .7))
        currentPosition = backUpToInitialPos2;
      Hardware::intakeMotor.move(-127);
    break;
    case backUpToInitialPos2:
      if(driveInches(20, -.7))
        currentPosition = turnToFlag;
      Hardware::intakeMotor.move(0);
    break;
    case turnToFlag:
      if(turnDegrees((Initialize::currentColor == Hardware::Color::red ? 1 : -1) * -90, .5))
        currentPosition = driveToFireDist2;
    break;
    case driveToFireDist2:
      if(driveInches(36, .7))
        currentPosition = fireBall2;
    break;
    case fireBall2:
      if(fireBall(Initialize::flagColor, false, true, true))
        {
          pros::delay(5000);
          Hardware::flywheelPID.setTarget(0);
        }
    case end:

    break;
  }
  pros::delay(20);
}
}
