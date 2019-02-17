#ifndef BALLSHOOTER_H
#define BALLSHOOTER_H
#define LOW_FLAG_HEIGHT
#define MID_FLAG_HEIGHT
#define HIGH_FLAG_HEIGHT

void spinUpFlywheel(int power);
bool fireBall(bool spinUpButton, bool fireButton, float distanceToFlag, float selected_flag_height);
bool setFlywheelSpeed(int rpm);
bool intakeBall(int direction);
#endif
