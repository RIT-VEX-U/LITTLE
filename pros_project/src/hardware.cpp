#include "api.h"
#include "hardware.h"

using namespace pros;

Motor Hardware::frontLeftMotor = Motor(12, false);
Motor Hardware::backLeftMotor = Motor(11, false);
Motor Hardware::frontRightMotor = Motor(14, true);
Motor Hardware::backRightMotor = Motor(13, true);

Motor Hardware::leftFlywheelMotor = Motor(2, false);
Motor Hardware::rightFlywheelMotor = Motor(1, true);
Motor Hardware::intakeMotor = Motor(3, false);

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

ADIGyro Hardware::gyro = ADIGyro(1, .1);
