#ifndef HARDWARE
#define HARDWARE
#include "api.h"

using namespace pros;

class Hardware
{
public:
  static Motor leftMotor;
  static Motor rightMotor;

  static Motor leftFlywheelMotor;
  static Motor rightFlywheelMotor;
  static Motor intakeMotor;

  static ADIGyro gyro;

  static Controller controller1;

  static Vision vis;
};
#endif
