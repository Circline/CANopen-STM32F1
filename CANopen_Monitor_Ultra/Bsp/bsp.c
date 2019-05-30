#include "bsp.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "bsp_usart.h"

void LED_Initializes(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);     //����ʱ��
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;                                 //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOE,&GPIO_InitStruct);                                            //��ʼ��IO
	
	GPIO_SetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
  RLED_ON();
	GLED_ON();
	BLED_ON();
}

void BSP_Init(void)
{
  LED_Initializes();                             //LED�ײ��ʼ��
  TIM_Initializes();                             //ϵͳʱ�����ʱ����ʼ������ʱ��ʱ����ʼ��
  
	USART_Initializes();                           //USART�ײ��ʼ��
	
	Lcd_Initialize();
	Touch_Init();
}
