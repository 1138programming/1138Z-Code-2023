#ifndef PID_HPP
#define PID_HPP

#include "vex.h"

class PID {
  private:
    double setpoint;

    double Kp = 0.0;
    double Ki = 0.0;
    double Kd = 0.0;

    double error = 0;
    double previousIntegral = 0;
    double previousError = 0;

    double outputMin = 0;
    double outputMax = 0;

    double bias = 0;
    double allowedError = 0.001;

    bool isFinished = false;

    std::uint32_t iterationTime = 0;
    std::uint32_t lastMillis = 1;

    double abs(double num) {
        return num < 0 ? -num : num;
    }

  public:
    PID(double setpoint, double Kp, double Ki, double Kd, double outputMax, double outputMin, double allowedError) {
      this->setpoint = setpoint;
      this->Kp = Kp;
      this->Ki = Ki;
      this->Kd = Kd;
      this->outputMax = outputMax;
      this->outputMin = outputMin;
      this->allowedError = allowedError;
      this->lastMillis = vex::timer::system();
    }

    void setSetpoint(double setpoint) {
      this->setpoint = setpoint;
    }

    bool isPIDFinished() {
      return this->isFinished;
    }

    double calculate(double process_var) {

      this->iterationTime = vex::timer::system() - lastMillis;

      if (abs(setpoint - process_var) < allowedError) {
        this->isFinished = true;
        return 0.0;
      }
      else {
        this->isFinished = false;
      }

      error = setpoint - process_var;

      double integral = previousIntegral + error * iterationTime;
      double derivative = (error - previousError) / iterationTime;

      double output = (Kp * error) + (Ki * integral) + (Kd * derivative) + (bias);

      this->previousError = error;
      this->previousIntegral = integral;

      // if (output > outputMax) {
      //   return outputMax;
      // }
      // else if (output < outputMin) {
      //   return outputMin;
      // }
      
      this->lastMillis = vex::timer::system();

      return output;
    }
};

#endif