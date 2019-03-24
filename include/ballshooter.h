#ifndef BALLSHOOTER
#define BALLSHOOTER

#include "hardware.h"

void spinUpFlywheel(int power);
bool fireBall(Hardware::Color color, bool closeShot, bool farShot, bool isInAuto);
bool setFlywheelSpeed(int rpm);
bool intakeBall(int direction);
bool autoAim(Hardware::Color color);
float getDistanceToTarget(int y, bool isHighFlag);
bool spinFlywheelToDistance(float inches, bool isHighFlag);
bool autoAimDistance(float ultVal, bool isHighFlag);
#endif
