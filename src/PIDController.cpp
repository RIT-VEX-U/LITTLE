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
}

float PIDController::step(){
  float velocity = victim->get_actual_velocity() * 35;
  error = target - velocity;
  dError = (error - lastError) / (deltaT / 1000);
  lastError = error;
  cumError += error;
  if(cumError > 20000){
    cumError = 20000;
  }else if(cumError < -20000){
    cumError = 20000;
  }

  return map((pGain * error) + (iGain * cumError));
}

void PIDController::setTarget(float targetVelocity){
  target = targetVelocity;
}


float PIDController::map(float value){
  float leftSpan = 7000;
  float rightSpan = 24000;
  float valueScaled = value / leftSpan;

  return -12000 + (valueScaled * rightSpan);
}
