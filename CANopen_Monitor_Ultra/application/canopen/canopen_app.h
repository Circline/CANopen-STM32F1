#ifndef _CANOPEN_APP_H
#define _CANOPEN_APP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_can.h"
/* �궨�� --------------------------------------------------------------------*/
#define CANOPEN_STACK_SIZE        128                      //CANOPEN�����ջ��С
#define CANOPEN_TASK_PRIORITY     2                        //CANOPEN�������ȼ�


/* �������� ------------------------------------------------------------------*/
void CANOpen_Node_Init(void);
void CANOpen_App_Task(void);

#endif /* _CANOPEN_APP_H */
