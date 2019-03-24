#include "PIDController.h"
#include "main.h"
#include "pros/rtos.h"
#include "hardware.h"

PIDController::PIDController(float p, float i, float d, float deltaTime, std::vector<pros::Motor *> victimList)
{
  pGain = p;
  iGain = i;
  dGain = d;
  deltaT = deltaTime;
  victims = victimList;
  lastError = 0;
  cumError = 0;
  pidOut = 0;
  dError = 0;
  error = 0;
  velocity = 0;

  task_handle = new pros::Task(task_function, (void*)this);
  task_handle->resume();
}

float PIDController::step(){
  velocity = victims[0]->get_actual_velocity() * 35;
  if(target == 0){
    return 0;
  }else{
    error = target - velocity;
    dError = (error - lastError) / deltaT;
    lastError = error;
    cumError += error;
    if(cumError > 200000){
      cumError = 200000;
    }else if(cumError < -200000){
      cumError = -200000;
    }

    pidOut = (pGain * error) + (iGain * cumError) + (dGain * dError);
    if (pidOut > 12000){
      pidOut = 12000;
    }else if(pidOut < -12000){
      pidOut = -12000;
    }
    return pidOut;
  }
}

void PIDController::setTarget(float targetVelocity){
  target = -targetVelocity;
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
      pros::lcd::print(2, "Target RPM: %f", controller->target);
      pros::lcd::print(3,"cumError: %f", controller->cumError);
      pros::lcd::print(4, "PID Out: %f, Error: %f", stepVal, controller->error);
      pros::lcd::print(5, "Controller Speed Read: %f", controller->victims[0]->get_actual_velocity() * 35);
      pros::delay(controller->deltaT * 1000);
  }


}
