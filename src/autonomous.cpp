#include "main.h"
#include "hardware.h"
#include "external_functions.h"
#define SPROCKET_ROTATION 2.3561925 // circumference in inches, distance traveled in one rotation

enum AutoPath
{
  init, turnToOurFlag1, fireMid1, driveToPushFlag, reverseFromPushFlag,
  turnToGetBall1, driveToBall1, reverseFromBall1, turnToMidFlag, fireMid2,
  turnToGetBall2, driveToBall2, reverseFromBall2, turnToOurFlag2, fireHigh1, end
};


AutoPath currentPosition = init;

// resets chassis encoders (all?)
void resetEncoders(){
  Hardware::leftMotor.set_zero_position(Hardware::leftMotor.get_position());
  Hardware::rightMotor.set_zero_position(Hardware::rightMotor.get_position());
}

// position robot so it's ready to shoot
void lineUp(){
  
}

// Drive to distance given
void driveDist(int inch){
  while(Hardware::leftMotor.get_position()*SPROCKET_ROTATION < inch){
    drive(100, 100); //lowered speed for more accuracy
  }
  drive(-20, -20); //quick brake if needed
  delay(500);
  drive(0, 0);
  resetEncoders();
}

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
  switch(currentPosition)
  {
    case init:

    break;
    case turnToOurFlag1:

    break;
    case fireMid1:

    break;
    case driveToPushFlag:

    break;
    case reverseFromPushFlag:

    break;
    case turnToGetBall1:

    break;
    case driveToBall1:

    break;
    case reverseFromBall1:

    break;
    case turnToMidFlag:

    break;
    case fireMid2:

    break;
    case turnToGetBall2:

    break;
    case driveToBall2:

    break;
    case reverseFromBall2:

    break;
    case turnToOurFlag2:

    break;
    case fireHigh1:

    break;
    case end:

    break;
  }
}
