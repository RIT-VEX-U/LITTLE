#ifndef HARDWARE
#define HARDWARE
#include "api.h"

using namespace pros;

class Hardware
{
public:
  static Motor frontLeftMotor;
  static Motor backLeftMotor;
  static Motor frontRightMotor;
  static Motor backRightMotor;

  static Motor frontLeftFlywheelMotor;
  static Motor backLeftFlywheelMotor;
  static Motor frontRightFlywheelMotor;
  static Motor backRightFlywheelMotor;

  static ADIGyro gyro;

  static Controller controller1;
};
#endif
