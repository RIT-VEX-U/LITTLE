#ifndef PID_H
#define PID_H
#include "main.h"
class PIDController{

  public:
    PIDController(float pGain, float iGain, float dGain, float deltaT,
                  pros::Motor victim);
    float step();
    float pidOut;
    void initTask();
    void setTarget(float targetVelocity);
    static float map(float value);
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
    pros::Motor *victim;
    pros::task_t task_handle;

    static void task_function(PIDController *controller);


};

void task_function(void* param);
#endif
