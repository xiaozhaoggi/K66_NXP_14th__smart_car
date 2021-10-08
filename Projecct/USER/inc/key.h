#ifndef _KEY_H_
#define _KEY_H_

#include "stdint.h"
extern uint8_t gRetValue_KEY1,gRetValue_KEY2,gRetValue_KEY3,gRetValue_KEY4,gRetValue_KEY5,gRetValue_KEY6,i;


//#define KEY1  PAin(27) 
//#define KEY2  PDin(5) 
#define KEY3  PAin(25) 
//#define KEY4  PDin(7) 
//#define KEY5  PDin(8) 
//#define KEY6  PDin(9) 
#define KEY6  PAin(7) 
//#define NO_KEY1          (0x00)
//#define KEY1_SINGLE      (0x01)
//#define NO_KEY2          (0x00)
//#define KEY2_SINGLE      (0x01)
#define NO_KEY3          (0x00)
#define KEY3_SINGLE      (0x01)
//#define NO_KEY4          (0x00)
//#define KEY4_SINGLE      (0x01)
//#define NO_KEY5          (0x00)
//#define KEY5_SINGLE      (0x01)
#define NO_KEY6          (0x00)
#define KEY6_SINGLE      (0x01)

typedef enum
{
    kKEY1_Idle,          /*空闲态 */
    kKEY1_Debounce,      /*确认与消抖态 */
    kKEY1_Confirm,       /*确认按键状态*/

    kKEY2_Idle,          /*空闲态 */
    kKEY2_Debounce,      /*确认与消抖态 */
    kKEY2_Confirm,       /*确认按键状态*/
	
    kKEY3_Idle,          /*空闲态 */
    kKEY3_Debounce,      /*确认与消抖态 */
    kKEY3_Confirm,       /*确认按键状态*/
	
    kKEY4_Idle,          /*空闲态 */
    kKEY4_Debounce,      /*确认与消抖态 */
    kKEY4_Confirm,       /*确认按键状态*/
	
    kKEY5_Idle,          /*空闲态 */
    kKEY5_Debounce,      /*确认与消抖态 */
    kKEY5_Confirm,       /*确认按键状态*/
	
	  kKEY6_Idle,          /*空闲态 */
    kKEY6_Debounce,      /*确认与消抖态 */
    kKEY6_Confirm,       /*确认按键状态*/
}KEY_Status;

void Flash_Write(void);
void Flash_Read(void);
void KEY_Scan(void);
void boma();



#endif
