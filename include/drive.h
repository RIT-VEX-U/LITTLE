#define SPROCKET_ROTATION 2.3561925 // circumference in inches, distance traveled in one rotation

//Driving Code
void drive(int leftMotor, int rightMotor);
void driveTank(float left, float right, bool square_inputs);
void driveMecanum(int leftYJoy, int leftXJoy, int rightXJoy, bool squareInputs, float deadband);
void driveMecanumRaw(float magnitude, float direction, float rotation, bool squareInputs, float deadband);

float getAbsValAvgEncVal(void);
bool driveInches(float inches, float speed);
bool turnDegrees(int degrees, float speed);
void resetEncoders(void);

//Turning
bool turn(float degrees, float speed);
void turnNoDeg(bool right, float speed);
