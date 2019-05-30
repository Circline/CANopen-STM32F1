#include "FreeRTOS.h"
#include "bsp.h"
#include "app.h"

/************************************************
�������� �� SysInit
��    �� �� ϵͳ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
void SysInit(void)
{
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

/************************************************
�������� �� main
��    �� �� ���������
��    �� �� ��
�� �� ֵ �� int
��    �� �� SWUST Tom
*************************************************/
int main(void)
{
  /* 1��SYS��ʼ�� */
  SysInit();

  /* 2���������� */
  AppTaskCreate();

  /* 3���������� */
  vTaskStartScheduler();

  return 0;
}

