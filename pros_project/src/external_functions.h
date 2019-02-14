#ifndef EXTERNAL_FUNCTIONS
#define EXTERNAL_FUNCTIONS

#define LOW_FLAG_HEIGHT
#define MID_FLAG_HEIGHT
#define HIGH_FLAG_HEIGHT
#define IN 127
#define OUT -127

//Ball Shooter
bool fireBall(bool spinUpButton, bool fireButton, float distanceToFlag, float selected_flag_height);
bool setFlywheelSpeed(int rpm);
bool intakeBall(int direction);

//Driving Code
void drive(int leftMotor, int rightMotor);
void driveTank(float left, float right, bool square_inputs);
void driveMecanum(int leftYJoy, int leftXJoy, int rightXJoy, bool squareInputs, float deadband);
void driveMecanumRaw(float magnitude, float direction, float rotation, bool squareInputs, float deadband);
#endif
