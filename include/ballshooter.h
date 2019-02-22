#ifndef BALLSHOOTER
#define BALLSHOOTER
enum Color
{
  blue, red
};

void spinUpFlywheel(int power);
bool fireBall(Color color, bool closeShot, bool farShot, bool isInAuto);
bool setFlywheelSpeed(int rpm);
bool intakeBall(int direction);
bool autoAim(Color color);
float getDistanceToTarget(int y, bool isHighFlag);
bool spinFlywheelToDistance(float inches, bool isHighFlag);
bool autoAimDistance(float ultVal, bool isHighFlag);
#endif
