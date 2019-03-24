#include "hardware.h"
#include "drive.h"

/**
	An easier wrapper for direct control tank drive.
*/
void drive(int leftMotor, int rightMotor)
{
	Hardware::leftMotor.move(leftMotor);
	Hardware::rightMotor.move(rightMotor);
}

/**
 *	Drives the robot using a tank-system.
 *
 *	Squaring the inputs allows slower control over the majority of the
 *	joystick band, but still allows fast movements near the end, following
 		a x^2 curve. Leave as false for a y=x linear function.
 */
void driveTank(float left, float right, bool square_inputs)
{

float left_out = left / 127.0;
float right_out = right / 127.0;

int left_sign = (left_out > 0) ? 1 : (left_out < 0) ? -1 : 0;
int right_sign = (right_out > 0) ? 1 : (right_out < 0) ? -1 : 0;

if(square_inputs)
{
	left_out = pow(left_out, 2) * left_sign;
	right_out = pow(right_out, 2) * right_sign;
}

drive((int)(left_out * 127), (int)(right_out * 127));
}



/**
* Drives the robot with a mecanum drivesystem, and with joystick inputs, between
* -127 and +127.
*
* If you set SquareInputs to true, you gain more control over small movements of
* the robot.
*
* Deadband is the percentage of joystick that the robot will not move, so that the
* motors aren't always receiving an input, and are constantly running. 0.1 is usually good.
*/
void driveMecanum(int leftYJoy, int leftXJoy, int rightXJoy, bool squareInputs, float deadband)
{
	float leftYIn = leftYJoy / 127.0;
	float leftXIn = leftXJoy / 127.0;
	float rightXIn = rightXJoy / 127.0;

	float magnitude = sqrt(pow((float)leftYIn, 2) + pow((float)leftXIn, 2));
	float direction = atan2(leftXIn, leftYIn);
	float rotation = rightXIn;

	driveMecanumRaw(magnitude, direction, rotation, squareInputs,deadband);
}

/**
*Drives the robot with a mecanum drive system, and direct magnitude / direction
* / rotation controls. Useful for auto.
* NOTE: set deadband and square inputs to 0 if you are running in auto.
*/
void driveMecanumRaw(float magnitude, float direction, float rotation, bool squareInputs, float deadband)
{
	//The wheels on the corner of the robot use the same formula, besides rotation.
	//Rotation is dertermined by whether the wheel is on the left or right side.
	float frontLeftOut = (magnitude * cos(direction - (3.14159 / 4.0))) + rotation;
	float backRightOut = (magnitude * cos(direction - (3.14159 / 4.0))) - rotation;
	float frontRightOut = (magnitude * cos(direction + (3.14159 / 4.0))) - rotation;
	float backLeftOut = (magnitude * cos(direction + (3.14159 / 4.0))) + rotation;
	//Limit the output between -1 and 1
	frontLeftOut = (frontLeftOut > 1) ? 1 : (frontLeftOut < -1) ? -1 : frontLeftOut;
	frontRightOut = (frontRightOut > 1) ? 1 : (frontRightOut < -1) ? -1 : frontRightOut;
	backLeftOut = (backLeftOut > 1) ? 1 : (backLeftOut < -1) ? -1 : backLeftOut;
	backRightOut = (backRightOut > 1) ? 1 : (backLeftOut < -1) ? -1 : backRightOut;

	if(squareInputs)
	{
		magnitude = (magnitude > 0 ? 1 : -1) * pow(magnitude, 2);
		rotation = (rotation > 0 ? 1 : -1) * pow(rotation, 2);
	}

		Hardware::leftMotor.move(frontLeftOut * 127);
		Hardware::rightMotor.move(frontRightOut * 127);
	}

	void resetEncoders()
	{
		Hardware::leftMotor.tare_position();
		Hardware::rightMotor.tare_position();
	}

/**
		Gets the average encoder value of all drive encoders. It also takes the
		absolute value before doing so to make sure positives and negatives
		don't cancel out when turning.
*/
	float getAbsValAvgEncVal()
	{
		return ((abs(Hardware::leftMotor.get_position())
		 + abs(Hardware::rightMotor.get_position())) / 2.0)
		 * ((3.14159 * 2.43) / 900.0);
	}

	bool driveInchesInit = true;
	/**
		Drives the robot X inches either forwards or backwards. It calculates how
		many inches the robot has driven given the average encoder inputs from the
		motors. Speed is in percent, -1.0 to 1.0.

		This also has dynamic stabilty by comparing the left side encoder to the
		right, and compensating for the difference betweeen the two.
	*/
	bool driveInches(float inches, float speed)
	{
		if(driveInchesInit)
			{
				resetEncoders();
				Hardware::gyro.reset();
				driveInchesInit = false;
			}
		if(getAbsValAvgEncVal() >= abs(inches))
			{
				drive(0,0);
				driveInchesInit = true;
				return true;
			}

		if(Hardware::gyro.get() > 0)
			drive((speed - .08)* 127, (speed +.08) * 127);
		else if(Hardware::gyro.get() < 0)
			drive((speed + .08)* 127, (speed - .08) * 127);
		else
			drive(speed * 127, speed * 127);

		return false;
	}

	bool turnDegreesInit = true;
	/**
		Turns the robot X degrees by using the robot turning circle to calculate the
		number of "inches" the robot should turn before it has reached x degrees.

		This uses the arc length formula, and encoders as the sensor.
	*/
	bool turnDegrees(int degrees, float speed)
	{
		if(turnDegreesInit)
		{
			Hardware::gyro.reset();
			turnDegreesInit = false;
		}

		if(fabs(Hardware::gyro.get()) >= abs(degrees))
		{
			drive(0,0);
			turnDegreesInit = true;
			return true;
		}

		drive(speed * (degrees > 0 ? 1 : -1) * 127, speed * (degrees > 0 ? -1 : 1) * 127);
		return false;
	}
