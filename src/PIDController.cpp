#include "PIDController.h"
#include "api.h"
#include "pros/rtos.h"

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

void PIDController::initTask(){
  task_handle = pros::c::task_create((pros::task_fn_t)task_function,
    (void*)this,
     TASK_PRIORITY_DEFAULT,
      TASK_STACK_DEPTH_DEFAULT,
       task_name);
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

void task_function(void* param){
  ((PIDController*)param)->cumError = 0;

  while(true){

  }
}
