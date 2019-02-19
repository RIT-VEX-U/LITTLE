#include "PIDController.h"
#include "main.h"
#include "pros/rtos.h"

PIDController::PIDController(float p, float i, float d, float deltaT, std::vector<pros::Motor *> victimList)
{
  pGain = p;
  iGain = i;
  dGain = d;
  deltaT = deltaT;
  victims = victimList;
  lastError = 0;
  cumError = 0;
  pidOut = 0;

  task_handle = new pros::Task(task_function, (void*)this);
  task_handle->resume();
}

float PIDController::step(){
  float velocity = victims[0]->get_actual_velocity() * 35;
  if(target == 0){
    return 0;
  }else{
    error = target - velocity;
    dError = (error - lastError) / (deltaT / 1000);
    lastError = error;
    cumError += error;

    return (pGain * error) + (iGain * cumError);
  }
}

void PIDController::setTarget(float targetVelocity){
  target = targetVelocity;
}

void task_function(void* param){
  PIDController *controller = ((PIDController*)param);
  controller->cumError = 0;
  controller->pidOut = 0;
  float stepVal;
  while(true){
      stepVal = controller->step();
      for(pros::Motor *m : controller->victims){
        m->move_voltage(stepVal);
      }
  }
  pros::delay(controller->deltaT);
}
