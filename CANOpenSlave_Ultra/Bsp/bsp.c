#include "bsp.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "bsp_usart.h"


/************************************************
�������� �� LED_Initializes
��    �� �� LED��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
void LED_Initializes(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);     //����ʱ��
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;                                 //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC,&GPIO_InitStruct);                                            //��ʼ��IO
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
 // RLED_ON();
}


/************************************************
�������� �� BSP_Init
��    �� �� �ײ�������ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� SWUST Tom
*************************************************/
void BSP_Init(void)
{
  LED_Initializes();                             //LED�ײ��ʼ��

  CAN_Initializes();                             //CAN�ײ��ʼ��
  TIM_Initializes();                             //TIM�ײ��ʼ��
  USART_Initializes();                           //USART�ײ��ʼ��
}
