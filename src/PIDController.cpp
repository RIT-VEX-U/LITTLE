#include "PIDController.h"

PIDController::PIDController(float p, float i, float d, float deltaT, pros::Motor motor)
{
  pGain = p;
  iGain = i;
  dGain = d;
  deltaT = deltaT;
  victim = &motor;
  lastError = 0;
  cumError = 0;
  pidOut = 0;
}

float PIDController::step(){
  float velocity = victim->get_actual_velocity() * 35;
  error = target - velocity;
  dError = (error - lastError) / (deltaT / 1000);
  lastError = error;
  cumError += error;

  return (pGain * error) + (iGain * cumError);
}

void PIDController::setTarget(float targetVelocity){
  target = targetVelocity;
}
