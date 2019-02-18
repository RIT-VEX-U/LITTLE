#ifndef HARDWARE
#define HARDWARE
#include "api.h"
#include "PIDController.h"

class Hardware
{
public:
  static pros::Motor leftMotor;
  static pros::Motor rightMotor;

  static pros::Motor leftFlywheelMotor;
  static pros::Motor rightFlywheelMotor;
  static pros::Motor intakeMotor;

  static PIDController flywheelPID;

  static pros::Motor flipperMotor;

  static pros::ADIGyro gyro;

  static pros::Controller controller1;

  static pros::Vision camera;
};
#endif
