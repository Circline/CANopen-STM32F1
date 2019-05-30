#include "main.h"

extern volatile GUI_TIMER_TIME OS_TimeMS;

int GUIFlag=0;
int CANopenFlag=0;

WM_HWIN hWinSetting;
WM_HWIN hWinWindow;

extern WM_HWIN Createsetting(void);
extern WM_HWIN CreateWindow(void);

extern void WinMain_DateUpdate(void);

SD_Error err;
int main()
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//��λ��ռ���ȼ���0λ�����ȼ�
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/*ϵͳ�����ʼ��*/
	BSP_Init();
	CANOpen_Driver_Init();
	/*emWin��ʼ��*/
	GUI_Init();
	WM_SetCreateFlags( WM_CF_MEMDEV);/*to use mem dev*/
	
	/*���ڳ�ʼ��*/
	//hWinSetting = Createsetting();
	hWinWindow = CreateWindow();
	
	while(1)
	{
		if(OS_TimeMS-GUIFlag>50)//20HZ
		{
			GUIFlag=OS_TimeMS;
			GUI_TOUCH_Exec();	
			GUI_Delay(1);
		}
		
		if(OS_TimeMS-CANopenFlag>50)//50HZ
		{
			CANopenFlag = OS_TimeMS;
			CANOpen_App_Task();
			WinMain_DateUpdate();
		}
	}
}
