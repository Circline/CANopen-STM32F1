#include "app.h"
#include "bsp.h"
#include "bsp_usart.h"
#include "canopen_app.h"


/* ��̬���� ------------------------------------------------------------------*/
static void APP_Init(void);
static void APP_Task(void *pvParameters);


/************************************************
�������� �� AppTaskCreate
��    �� �� ��������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
void AppTaskCreate(void)
{
  BaseType_t xReturn;

  /* ����Ӧ�ó���(��ʼ����) */
  xReturn = xTaskCreate(APP_Task, "APP_Task", APP_STACK_SIZE, NULL, APP_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    printf("APP_Task create failed");
    return;                                      //��������ʧ��
  }
}

/************************************************
�������� �� APP_Init
��    �� �� Ӧ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
static void APP_Init(void)
{
  CANOpen_App_Init();
}

/************************************************
�������� �� APP_Task
��    �� �� Ӧ�ó���(��ʼ����)
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
static void APP_Task(void *pvParameters)
{
  BSP_Init();                                    //�ײ�������ʼ��
  APP_Init();                                    //Ӧ�ó����ʼ��

  for(;;)
  {
    vTaskDelay(50);
		
    BLED_TOGGLE();                                //LED��˸
  }
}
