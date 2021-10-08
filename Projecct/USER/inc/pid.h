#ifndef _PID_H_
#define _PID_H_
#include "headfile.h"

extern struct PID_Control SE_PID;
extern struct PID_Control Motor_PID;;
struct PID_Control
{
	int32 Setpoint;
	int Lasterror;
	int Preerror;
	int Kp;
	int Ki;
	int Kd;
	int32 pwm;
};

void SE_control();
void Motor_control();
void SE_PID_init();
void Motor_PID_init();
void hgzhixian();
void SPEED_Filter(int16 Speed);
void motor_speedcontrol();
int regression(int startline,int endline);
extern int kk,S_e0,S_e1,S_kp,S_kd,Kp_e;
extern int M_kp,M_ki,M_kd,M_e0;
extern int16 M_nowpoint,M_setpoint;
extern int xielv;
extern int error;
extern int str_flag,turn_flag,turning_flag;



#endif