#include "api.h"
#include "hardware.h"

using namespace pros;

Motor Hardware::frontLeftMotor = Motor(10, false);
Motor Hardware::backLeftMotor = Motor(9, false);
Motor Hardware::frontRightMotor = Motor(1, true);
Motor Hardware::backRightMotor = Motor(2, true);

Motor Hardware::leftFlywheelMotor = Motor(5, false);
Motor Hardware::rightFlywheelMotor = Motor(4, true);
Motor Hardware::intakeMotor = Motor(3, false);

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

ADIGyro Hardware::gyro = ADIGyro(1, .1);
