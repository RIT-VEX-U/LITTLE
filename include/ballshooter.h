#ifndef BALLSHOOTER
#define BALLSHOOTER
enum Color
{
  blue, red
};

void spinUpFlywheel(int power);
bool fireBall(bool spinUpButton, bool fireButton, float distanceToFlag, float selected_flag_height);
bool setFlywheelSpeed(int rpm);
bool intakeBall(int direction);
bool autoAim(Color color);
float getDistanceToTarget(int y, bool isHighFlag);
bool spinFlywheelToDistance(float inches, bool isHighFlag);
#endif
