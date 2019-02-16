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
  float velocity = victim->get_actual_velocity() * 35;
  error = targetVelocity - velocity;
  dError = (error - lastError) / (deltaT / 1000);
  lastError = error;
  cumError += error;
  if(cumError > 400){
    cumError = 400;
  }

  return map(pGain * error + iGain * cumError + dError * dGain);
}

void PIDController::setTarget(float targetVelocity){
  targetVelocity = targetVelocity;
}

float map(float value){
  float leftSpan = 800;
  float rightSpan = 24000;


  float valueScaled = value / leftSpan;

  return -12000 + (valueScaled * rightSpan);
}
