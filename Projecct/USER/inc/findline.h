#ifndef _FINDLINE_H_
#define _FINDLINE_H_




#include "SEEKFREE_7725.h"
//#define TRIG_PIN D9                //定义超声波触发引脚端口
//#define ECHO_PIN D10                //定义超声波触发引脚端口
#define  zuo_huandao 3
#define  you_huandao 4         
#define jump_point   7   //调变点个数，检测起跑线用   （误判加大  判断不出减小）
#define jump_point_row 2//检测到多少行满足条件的为起跑线 （误判加大 判断不出减小）
extern int x,y,mindline;
extern int Lline[60],Mline[60],Rline[60],L_lost_flag[60],R_lost_flag[60];
extern int w_error1,w_error2;
extern void Mfindline();
extern void jiaquan_error1();
extern void jiaquan_error2(void);
extern void shizi();
//void zhidao();
//void turn();
extern void Mfindline_plus();
extern void findline();
extern void zhangai_duanlu();
extern void huandao();
extern void heixian();
extern int ZAbiaozhi,HDbiaozhi,DLbiaozhi;
extern void jizhunhang();
extern void youxiaohang();
void        yangguang();
extern int yxh;
extern int avrMline;
extern int shizi_flag,yxh_flag;
extern int yangguang_flag;
extern int dianci_sup_flag;
extern void chaoshengbo();
void dianci_sup();
extern long wait_time;                 //超时检测变量
extern uint32 distance_time ,distance;           //测距的时间变量 //转换出来的距离  单位为厘米
void Check_stop(void);// 起跑线检测








#endif

