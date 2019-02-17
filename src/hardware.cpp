#include "api.h"
#include "hardware.h"

using namespace pros;

Motor Hardware::leftMotor = Motor(1, false);
Motor Hardware::rightMotor = Motor(10, true);

Motor Hardware::leftFlywheelMotor = Motor(9, true);
Motor Hardware::rightFlywheelMotor = Motor(2, false);
Motor Hardware::intakeMotor = Motor(3, false);
Motor Hardware::flipperMotor = Motor(4,false);

PIDController flywheelPID = PIDController(1,.05,0,20,Hardware::leftFlywheelMotor);

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

ADIGyro Hardware::gyro = ADIGyro(1, .1);

Vision Hardware::camera = Vision(5);
