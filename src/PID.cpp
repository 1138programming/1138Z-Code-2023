#include "main.h"

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

    std::uint32_t iterationTime = 0; // PLEASE change this to use UNIX time on the actual bot code, I'm just doing this to write it rn.
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
      this->lastMillis = pros::millis();
    }

    double setSetpoint(double setpoint) {
      this->setpoint = setpoint;
    }

    double calculate(double process_var) {

      this->iterationTime = pros::millis() - lastMillis;

      if (abs(setpoint - process_var) < allowedError) {
        return 0.0;
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
      
      this->lastMillis = pros::millis();

      return output;
    }
};