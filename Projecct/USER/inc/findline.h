#ifndef _FINDLINE_H_
#define _FINDLINE_H_




#include "SEEKFREE_7725.h"
//#define TRIG_PIN D9                //���峬�����������Ŷ˿�
//#define ECHO_PIN D10                //���峬�����������Ŷ˿�
#define  zuo_huandao 3
#define  you_huandao 4         
#define jump_point   7   //���������������������   �����мӴ�  �жϲ�����С��
#define jump_point_row 2//��⵽����������������Ϊ������ �����мӴ� �жϲ�����С��
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
extern long wait_time;                 //��ʱ������
extern uint32 distance_time ,distance;           //����ʱ����� //ת�������ľ���  ��λΪ����
void Check_stop(void);// �����߼��








#endif

