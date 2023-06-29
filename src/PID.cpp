class PID {
  private:
    float setpoint;

    float Kp = 0.0;
    float Ki = 0.0;
    float Kd = 0.0;

    float error = 0;
    float previousIntegral = 0;
    float previousError = 0;

    float outputMin = 0;
    float outputMax = 0;

    float iterationTime = 0; // PLEASE change this to use UNIX time on the actual bot code, I'm just doing this to write it rn.

    float bias = 0;
    float allowedError = 0.001;

    float abs(float num) {
        return num < 0 ? -num : num;
    }

  public:
    PID(float setpoint, float iterationTime, float Kp, float Ki, float Kd, float outputMax, float outputMin, float allowedError) {
      this->setpoint = setpoint;
      this->iterationTime = iterationTime;
      this->Kp = Kp;
      this->Ki = Ki;
      this->Kd = Kd;
      this->outputMax = outputMax;
      this->outputMin = outputMin;
      this->allowedError = allowedError;
    }

    float calculate(float process_var) {

      if (abs(setpoint - process_var) < allowedError) {
        return 0.0;
      }

      error = setpoint - process_var;

      float integral = previousIntegral + error * iterationTime;
      float derivative = (error - previousError) / iterationTime;

      float output = (Kp * error) + (Ki * integral) + (Kd * derivative) + (bias);

      this->previousError = error;
      this->previousIntegral = integral;

      // if (output > outputMax) {
      //   return outputMax;
      // }
      // else if (output < outputMin) {
      //   return outputMin;
      // }

        return output;
      
    }
};