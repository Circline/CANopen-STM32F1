#include "GUI.h"
#include "malloc.h"

//#define USE_EXRAM 0
///����EMWIN�ڴ��С
//#define GUI_NUMBYTES  200*1024
//#define GUI_BLOCKSIZE 32  //���С

#define GUI_NUMBYTES  (1024) *  50   // x KByte

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/* 32 bit aligned memory area */
U32 extMem[GUI_NUMBYTES / 4];

//GUI_X_Config
//��ʼ����ʱ�����,��������emwin��ʹ�õ��ڴ�
void GUI_X_Config(void) {
//	if(USE_EXRAM) //ʹ���ⲿRAM
//	{	
	//	U32 *aMemory = mymalloc(SRAMEX,GUI_NUMBYTES); //���ⲿSRAM�з���GUI_NUMBYTES�ֽڵ��ڴ�
//		GUI_ALLOC_AssignMemory((void*)aMemory, GUI_NUMBYTES); //Ϊ�洢����ϵͳ����һ���洢��
//		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //���ô洢���ƽ���ߴ�,����Խ��,���õĴ洢������Խ��
//		GUI_SetDefaultFont(GUI_FONT_6X8); //����Ĭ������
//	}else  //ʹ���ڲ�RAM
//	{
//		U32 *aMemory = mymalloc(SRAMIN,GUI_NUMBYTES); //���ڲ�RAM�з���GUI_NUMBYTES�ֽڵ��ڴ�
//		GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //Ϊ�洢����ϵͳ����һ���洢��
//		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //���ô洢���ƽ���ߴ�,����Խ��,���õĴ洢������Խ��
		GUI_ALLOC_AssignMemory(extMem, GUI_NUMBYTES);
	
		GUI_SetDefaultFont(GUI_FONT_8X16);
		//GUI_SetDefaultFont(GUI_FONT_6X8); //����Ĭ������
	//}
}
