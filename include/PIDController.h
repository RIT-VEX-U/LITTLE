#ifndef PID_H
#define PID_H
#include <vector>
#include "main.h"

class PIDController{

  public:
    PIDController(float pGain, float iGain, float dGain, float deltaT,
                  std::vector<pros::Motor *> victimList);
    float step();
    float pidOut;
    void initTask();
    void setTarget(float targetVelocity);
    const char* task_name;
    float pGain;
    float iGain;
    float dGain;
    float cumError;
    float error;
    float lastError;
    float dError;
    float deltaT;
    float target;
    pros::task_t task_handle;
    std::vector<pros::Motor *> victims;



};

void task_function(void* param);
#endif
