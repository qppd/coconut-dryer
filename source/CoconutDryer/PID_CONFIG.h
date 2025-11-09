#include <PID_v1.h>

double THRESHOLD_1 = 4;
double THRESHOLD_2 = 0;
double THRESHOLD_3 = 22;

double PID_OUTPUT_1 = 0;
double PID_OUTPUT_2 = 0;

PID pid(&CURRENT_TEMPERATURE, &PID_OUTPUT_1, &TEMPERATURE_SETPOINT, THRESHOLD_1, THRESHOLD_2, THRESHOLD_3, DIRECT);

//-----------------------------------------------------------------
//FUNCTION FOR INITIALIZING PID CONTROLLER-------------------------
//-----------------------------------------------------------------
void initPID() {
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 5000);  // Adjust these limits based on your system
}



//-----------------------------------------------------------------
//FUNCTION FOR MAINTAINING TEMPERATURE ----------------------------
//-----------------------------------------------------------------
void pidCOMPUTE() {
  pid.Compute();
  if (PID_OUTPUT_1 > 0) {
    operateSSR(RELAY_1, true);
    operateSSR(RELAY_2, true);
    operateSSR(RELAY_3, false);
  } else {
    operateSSR(RELAY_1, false);
    operateSSR(RELAY_2, false);
    operateSSR(RELAY_3, true);
  }
}
