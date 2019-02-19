#include "main.h"
#include "hardware.h"
#include "drive.h"
#define SPROCKET_ROTATION 2.3561925 // circumference in inches, distance traveled in one rotation
#define COLOR_AIM 1 // 1 = red, 2 = blue

pros::vision_signature RED_SIG = pros::Vision::signature_from_utility(1, -3817, -3307, -3562, 12179, 13435, 12807, 8.8, 0);//BLUE
pros::vision_signature BLUE_SIG = pros::Vision::signature_from_utility(2, 8595, 8905, 8750, -717, -353, -535, 8.8, 0);//RED

enum AutoPath
{
  init, turnToOurFlag1, fireMid1, driveToPushFlag, reverseFromPushFlag,
  turnToGetBall1, driveToBall1, reverseFromBall1, turnToMidFlag, fireMid2,
  turnToGetBall2, driveToBall2, reverseFromBall2, turnToOurFlag2, fireHigh1, end
};


AutoPath currentPosition = init;

// set vision vision signatures
void setSig(){
  Hardware::camera.set_signature(1, &RED_SIG);
  Hardware::camera.set_signature(2, &BLUE_SIG);
}

// resets chassis encoders (all?)
void resetEncoders(){
  Hardware::leftMotor.set_zero_position(Hardware::leftMotor.get_position());
  Hardware::rightMotor.set_zero_position(Hardware::rightMotor.get_position());
}

// position robot so it's ready to shoot (vision sensor needed)
void lineUp(int sig_num){
  while(Hardware::camera.get_by_sig(0, sig_num).left_coord > 0){ // is coordinate 0 centerd?
    turnNoDeg(0, 100);
  }
  while(Hardware::camera.get_by_sig(0, sig_num).left_coord < 0){ // is coordinate 0 centerd?
    turnNoDeg(1, 100);
  }
  turnNoDeg(0, 0);
}

//

// Drive to distance given
void driveDist(int inch){
  while(Hardware::leftMotor.get_position()*SPROCKET_ROTATION < inch){
    drive(100, 100); //lowered speed for more accuracy
  }
  drive(-20, -20); //quick brake if needed
  pros::delay(500);
  drive(0, 0);
  resetEncoders();
}

//Fire loaded ball
void shoot(){
  Hardware::leftFlywheelMotor.move(127);
  Hardware::rightFlywheelMotor.move(127);
  pros::delay(2000);
  Hardware::leftFlywheelMotor.move(127);
  Hardware::rightFlywheelMotor.move(127);
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
void autonomous() { // MOST IF NOT ALL OF THESE VALUES ARE GUESSES
  switch(currentPosition) // (bc we can't know the exact angle it will turn to face the flag, human error in set up)
  {
    case init:
      setSig();
    break;
    case turnToOurFlag1:
      lineUp(COLOR_AIM);
    break;
    case fireMid1:
      shoot();
    break;
    case driveToPushFlag:
      driveDist(48);
    break;
    case reverseFromPushFlag:
      driveDist(-10);
    break;
    case turnToGetBall1:
      turn(-45, 100);
    break;
    case driveToBall1:
      driveDist(48);
      turn(20, 100);
      driveDist(10);
    break;
    case reverseFromBall1:
      driveDist(-10);
    break;
    case turnToMidFlag:
      turn(90, 100);
      lineUp(COLOR_AIM);
    break;
    case fireMid2:
      shoot();
    break;
    case turnToGetBall2:
      turn(10, 100);
    break;
    case driveToBall2:
      driveDist(30);
    break;
    case reverseFromBall2:
      driveDist(-30);
    break;
    case turnToOurFlag2:
      turn(-10, 100);
      lineUp(COLOR_AIM);
    break;
    case fireHigh1:
      shoot();
    break;
    case end:
      // climbing alliance platform
      driveDist(-24);
      turn(-90, 100);
      driveDist(48);
    break;
  }
}
