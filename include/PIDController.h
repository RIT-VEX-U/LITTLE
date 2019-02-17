#include "main.h"
class PIDController{

  public:
    PIDController(float pGain, float iGain, float dGain, float deltaT,
                  pros::Motor victim);
    float step();
    void setTarget(float targetVelocity);
    static float map(float value);

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


};
