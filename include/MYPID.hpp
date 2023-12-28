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

    bool doubleWithinMarginOfError(double num, double target, double margin) {
        double min = target - (margin / 2.0);
        double max = target + (margin / 2.0);
        return num >= min && num <= max;
    }
    double absD(double val) {
      return val < 0 ? -val : val;
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
      this->isFinished = false;
    }
    void setAllowedError(double allowedError) {
      this->allowedError = allowedError;
      this->isFinished = false;
    }

    bool isPIDFinished() {
      return (this->isFinished) == true;
    }

    double calculate(double process_var) {
      if (this->isFinished) {
        return 0;
      }

      this->iterationTime = vex::timer::system() - lastMillis;

      if (doubleWithinMarginOfError(process_var, this->setpoint, this->allowedError)) {
        this->isFinished = true;
        return 0.0;
      }

      error = setpoint - process_var;

      double integral = previousIntegral + error * iterationTime;
      double derivative = (error - previousError) / iterationTime;

      double output = (Kp * error) + (Ki * integral) + (Kd * derivative) + (bias);

      this->previousError = error;
      this->previousIntegral = integral;

      if (output > outputMax) {
        return outputMax;
      }
      else if (output < outputMin) {
        return outputMin;
      }
      
      this->lastMillis = vex::timer::system();

      return output;
    }
};

#endif