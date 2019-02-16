#include "PIDController.h"

PIDController::PIDController(float pGain, float iGain, float dGain, float deltaT,
                            pros::Motor *victim)
{
  pGain = pGain;
  iGain = iGain;
  dGain = dGain;
  deltaT = deltaT;
  victim = victim;
  lastError = 0;
  cumError = 0;

}

float PIDController::step(){
  float velocity = victim->get_actual_velocity();
  error = targetVelocity - velocity;
  dError = (error - lastError) / (deltaT / 1000);
  lastError = error;
  cumError += error;

}

void PIDController::setTarget(float targetVelocity){
  targetVelocity = targetVelocity;
}
