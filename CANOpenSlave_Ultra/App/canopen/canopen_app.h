/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _CANOPEN_APP_H
#define _CANOPEN_APP_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include "bsp.h"
/* �궨�� --------------------------------------------------------------------*/
#define CANOPEN_STACK_SIZE        128                      //CANOPEN�����ջ��С
#define CANOPEN_TASK_PRIORITY     2                        //CANOPEN�������ȼ�


/* �������� ------------------------------------------------------------------*/
void CANOpen_App_Init(void);


#endif /* _CANOPEN_APP_H */

/**** Copyright (C)2019 SWUST Tom. All Rights Reserved **** END OF FILE ****/
