//Driving Code
void drive(int leftMotor, int rightMotor);
void driveTank(float left, float right, bool square_inputs);
void driveMecanum(int leftYJoy, int leftXJoy, int rightXJoy, bool squareInputs, float deadband);
void driveMecanumRaw(float magnitude, float direction, float rotation, bool squareInputs, float deadband);
