/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 5
  #define LEFT_MOTOR_BACKWARD  6
  #define RIGHT_MOTOR_FORWARD  9
  #define LEFT_MOTOR_FORWARD   10
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_ENABLE 13
#endif
#ifdef BTS_MOTOR_DRIVER
//RIGHT SIDE MOTORS
#define R_PWM_RIGHT_SIDE 2 //PWM 2
#define L_PWM_RIGHT_SIDE 3 //PWM 3
#define L_EN_RIGHT_SIDE  23 //23
#define R_EN_RIGHT_SIDE  25 //25

//LEFT SIDE MOTORS
#define R_PWM_LEFT_SIDE   4 //PWM 4
#define L_PWM_LEFT_SIDE   5 //PWM 5
#define L_EN_LEFT_SIDE   27 //27
#define R_EN_LEFT_SIDE   29 //29

#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
