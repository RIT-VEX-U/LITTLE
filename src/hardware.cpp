#include "api.h"
#include "hardware.h"

using namespace pros;

Motor Hardware::leftMotor = Motor(10, true);
Motor Hardware::rightMotor = Motor(1, false);

Motor Hardware::leftFlywheelMotor = Motor(9, true);
Motor Hardware::rightFlywheelMotor = Motor(2, false);
Motor Hardware::intakeMotor = Motor(3, false);
Motor Hardware::flipperMotor = Motor(4,false);

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

ADIGyro Hardware::gyro = ADIGyro(1, .1);

Vision Hardware::vis = Vision(5);
