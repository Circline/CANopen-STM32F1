/**
  ******************************************************************************
  * @�ļ���     �� canopen_app.c
  * @����       �� SWUST Tom
  * @�汾       �� V1.0.0
  * @����       �� 2019��5��20��
  * @ժҪ       �� CANOpenӦ�ó���Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2019��5��20�� V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "canopen_app.h"
#include "canopen_drv.h"
#include "Slave.h"
#include "node_config.h"

#include "bsp.h"



/* ��̬���� ------------------------------------------------------------------*/
static void CANOpen_App_Task(void *pvParameters);


/************************************************
�������� �� CANOpen_App_Init
��    �� �� CANOpenӦ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
void CANOpen_App_Init(void)
{
  BaseType_t xReturn;

  CANOpen_Driver_Init();

  xReturn = xTaskCreate(CANOpen_App_Task, "CANOpen_App_Task", CANOPEN_STACK_SIZE, NULL, CANOPEN_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    return;                                      //������������ʧ��
  }
}

/************************************************
�������� �� CANOpen_App_Task
��    �� �� CANOpenӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
static void CANOpen_App_Task(void *pvParameters)
{
  unsigned char nodeID = SLAVE_NODE_ID;                   //�ڵ�ID

  setNodeId(&Slave_Data, nodeID);
  setState(&Slave_Data, Initialisation);
  setState(&Slave_Data, Operational);

  while(1)
  {
		vTaskDelay(50);
		if(getState(&Slave_Data)!=Operational) RLED_OFF();
		else RLED_TOGGLE();
    Temperture[0]+=0.05;
    /* Ӧ�ô��� */
  }
}


