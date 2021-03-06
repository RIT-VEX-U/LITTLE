#include "api.h"
#include "hardware.h"
#include "PIDController.h"
#include "okapi/api.hpp"

using namespace pros;

Motor Hardware::leftMotor = Motor(1, false);
Motor Hardware::rightMotor = Motor(10, true);

Motor Hardware::leftFlywheelMotor = Motor(9, true);
Motor Hardware::rightFlywheelMotor = Motor(2, false);
Motor Hardware::intakeMotor = Motor(3, false);
Motor Hardware::flipperMotor = Motor(4,false);


PIDController Hardware::flywheelPID = PIDController(2,.1,.01,.02,{&Hardware::rightFlywheelMotor});

Controller Hardware::controller1 = Controller(E_CONTROLLER_MASTER);

okapi::ADIGyro Hardware::gyro = okapi::ADIGyro(3, .1);

ADIUltrasonic Hardware::ult1 = ADIUltrasonic(1,2);

Vision Hardware::camera = Vision(5);
