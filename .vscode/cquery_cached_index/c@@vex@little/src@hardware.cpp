#include "api.h"
#include "hardware.h"

using namespace pros;

Motor Hardware::frontLeftMotor = Motor(10, false);
Motor Hardware::backLeftMotor = Motor(8, false);
Motor Hardware::frontRightMotor = Motor(3, true);
Motor Hardware::backRightMotor = Motor(5, true);

Motor Hardware::leftFlywheelMotor = Motor(9, false);
Motor Hardware::rightFlywheelMotor = Motor(2, true);
Motor Hardware::intakeMotor = Motor(3, false);
Motor Hardware::flipperMotor = Motor(4,false);

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

ADIGyro Hardware::gyro = ADIGyro(1, .1);
