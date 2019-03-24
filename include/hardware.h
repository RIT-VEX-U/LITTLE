#ifndef HARDWARE
#define HARDWARE
#include "api.h"
#include "PIDController.h"
#include "okapi/api.hpp"

class Hardware
{
public:

  enum Color
  {
    red, blue
  };

  static pros::Motor leftMotor;
  static pros::Motor rightMotor;

  static pros::Motor leftFlywheelMotor;
  static pros::Motor rightFlywheelMotor;
  static pros::Motor intakeMotor;

  static PIDController flywheelPID;

  static pros::Motor flipperMotor;

  static pros::ADIUltrasonic ult1;
  static okapi::ADIGyro gyro;
  static pros::Vision camera;

  static pros::Controller controller1;

  //static pros::Vision camera;
};
#endif
