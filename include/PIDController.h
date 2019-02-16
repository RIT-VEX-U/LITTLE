#include "main.h"
class PIDController{

  public:
    PIDController(float pGain, float iGain, float dGain, float deltaT,
                  pros::Motor *victim);
    float step();
    void setTarget(float targetVelocity);
    float map(float value);

  private:
    float pGain;
    float iGain;
    float dGain;
    float cumError;
    float error;
    float lastError;
    float dError;
    float deltaT;
    float targetVelocity;
    pros::Motor *victim;


};
