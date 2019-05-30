#include  "touch.h"
#include "delay.h"
unsigned int  Data_is_ready=0;
unsigned char Touch_Buff[10]={0};
int Pointx1=1,Pointy1=1;
float TP_X=-1,TP_Y=-1;
/****************************************************************************************
																	��?��Y?�� I2C �̡�2??y?��
***************************************************************************************/
	
//*************************************************
//o����y??3? : void Touch_GPIO_Config(void)  
//1|?��?����? : ����??�䣤?����?IIC��y??,��?����?t?��?a��?��?��������??IIC1|?��
//��?��?2?��y : 
//��?3?2?��y : 
//����???��   : 
//*************************************************

unsigned char R_ACK;

//����SDA�ź���Ϊ����ģʽ
void SDA_Input_Mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = FT_SDA_Pin;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 

  	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

//����SDA�ź���Ϊ���ģʽ
void SDA_Output_Mode()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = FT_SDA_Pin;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

  	GPIO_Init(GPIOG, &GPIO_InitStructure);
}


/************************************************
*	o�� ��y ??: I2C_Start
*	1|?��?��?��: CPU����?eI2C����??����?1D?o?
*	D?    2?��o?T
*	���� ?? ?��: ?T
**************************************************/ 
void Touch_IIC_Start(void)
{
	Touch_SDA_OUT();     //sda??��?3?
	Touch_IIC_SDA(1);	  	  
	Touch_IIC_SCL(1);
	delay_us(4);
 	Touch_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	Touch_IIC_SCL(0);//?����?I2C����??��?��?��?����?��?��?����?��y?Y 
}	  
/****************************************************
*	o�� ��y ??: I2C_Stop
*	1|?��?��?��: CPU����?eI2C����??����?1D?o?
*	D?    2?��o?T
*	���� ?? ?��: ?T
****************************************************/
void Touch_IIC_Stop(void)
{
	Touch_SDA_OUT();//sda??��?3?
	Touch_IIC_SCL(0);
	Touch_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	Touch_IIC_SCL(1); 
	Touch_IIC_SDA(1);//����?��I2C����???����?D?o?
	delay_us(4);							   	
}
//�̨���y��|��eD?o?��?����
//����???�̡�o1��??����?��|��e����㨹
//        0��??����?��|��e3��1|
u8 Touch_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	Touch_SDA_IN();      //SDA����???a��?��?  
	Touch_IIC_SDA(1);//delay_us(2);	   
	Touch_IIC_SCL(1);//delay_us(2);	 
	while(Touch_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			Touch_IIC_Stop();
			return 1;
		}
	}
	Touch_IIC_SCL(0);//����?����?3?0 	   
	return 0;  
} 
/************************************** 
*	o�� ��y ??: I2C_Ack
*	1|?��?��?��: CPU2��������???ACKD?o?
*	D?    2?��o?T
*	���� ?? ?��: ?T 
**************************************/
void Touch_IIC_Ack(void)
{
	Touch_IIC_SCL(0);
	Touch_SDA_OUT();
	Touch_IIC_SDA(0);
	delay_us(4);
	Touch_IIC_SCL(1);
	delay_us(4);
	Touch_IIC_SCL(0);
}
/*************************************************
*	o�� ��y ??: I2C_NoAck
*	1|?��?��?��: CPU2������1??NACKD?o?
*	D?    2?��o?T
*	���� ?? ?��: ?T
*************************************************/	    
void Touch_IIC_NAck(void)
{
	Touch_IIC_SCL(0);
	Touch_SDA_OUT();
	Touch_IIC_SDA(1);
	delay_us(4);
	Touch_IIC_SCL(1);
	delay_us(4);
	Touch_IIC_SCL(0);
}				 				     
//IIC����?����???��??��
//����??�䨮?����D?T��|��e
//1��?��D��|��e
//0��??T��|��e			  
void Touch_IIC_Send_Byte(u8 txd)
{                        
	u8 t;   
	Touch_SDA_OUT(); 	    
	Touch_IIC_SCL(0);//��-�̨�����?��?a��?��y?Y��?��?
	for(t=0;t<8;t++)
	{              
		Touch_IIC_SDA((txd&0x80)>>7);
		txd<<=1; 	  
	delay_us(4);   //??TEA5767?a��y???������??��?��?D?��?
	Touch_IIC_SCL(1);
	delay_us(4); 
	Touch_IIC_SCL(0);	
	delay_us(4);
	}	 
} 	       
/************************************************
*	o�� ��y ??: I2C_Read_Byte
*	1|?��?��?��: CPU�䨮I2C����??������??����?8bit��y?Y
*	D?    2?��o?T
*	���� ?? ?��: ?����?��?��y?Y
*************************************************/
//?��1??��??����?ack=1������?����?��ACK��?ack=0��?����?��nACK   
u8 Touch_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	Touch_SDA_IN();//SDA����???a��?��?
    for(i=0;i<8;i++ )
	{
    Touch_IIC_SCL(0); 
    delay_us(4);
		Touch_IIC_SCL(1);
    receive<<=1;
    if(Touch_READ_SDA)receive++;   
		delay_us(2); 
  }					 
    if (!ack)
        Touch_IIC_NAck();//����?��nACK
    else
        Touch_IIC_Ack(); //����?��ACK   
    return receive;
}

unsigned char dat[10]={0};

unsigned char FT6336G_RD_Reg(unsigned char RegIndex,unsigned char *pbuf,unsigned char len)
{
	unsigned char receive=0;
	unsigned int i;

	Touch_IIC_Start();
	Touch_IIC_Send_Byte(FT6206_ADDR);
	Touch_IIC_Wait_Ack();
	Touch_IIC_Send_Byte(RegIndex);
	R_ACK=Touch_IIC_Wait_Ack();

	Touch_IIC_Start();
	Touch_IIC_Send_Byte(FT6206_ADDR+1);
	Touch_IIC_Wait_Ack();	
	for(i=0;i<len;i++)
	{
		if(i==(len-1))  *(pbuf+i)=Touch_IIC_Read_Byte(0);
		else            *(pbuf+i)=Touch_IIC_Read_Byte(1);
	}		
	Touch_IIC_Stop();	 
	receive=1;
	return receive;
}

unsigned char FT6336G_WR_Reg(unsigned char RegIndex,unsigned char *pbuf,unsigned char len)
{
	unsigned int i,j;
	Touch_IIC_Start();
	Touch_IIC_Send_Byte(FT6206_ADDR);
	Touch_IIC_Wait_Ack();
	Touch_IIC_Send_Byte(RegIndex);
	Touch_IIC_Wait_Ack();
	for(i=0; i<len; i++)
	{
		j=0;
		do
		{
			Touch_IIC_Send_Byte(pbuf[i]);
			
			if(++j >= 1000)	//Time Out
			{
				Touch_IIC_Stop();
				return 1;
			}
		}while(Touch_IIC_Wait_Ack());	//Read Ack
	}
	
	Touch_IIC_Stop();	 
	return 0;
}


int Get_TOUCH_X_MeasureX(void)
{
	FT6336G_RD_Reg(0x00,(unsigned char *)&Touch_Buff,7);

	if ((Touch_Buff[2]&0x01) == 1)
	{	
		Pointx1 = (((unsigned int)(Touch_Buff[3] & 0x0F)<<8 | (unsigned int)Touch_Buff[4]));
		Pointy1 = (((unsigned int)(Touch_Buff[5] & 0x0F)<<8 | (unsigned int)Touch_Buff[6]));
		if(Pointy1==0)
			Pointx1=0;	
	}
	else
	{
		Pointy1 =-1;
		Pointx1 =-1;		
	}
	return Pointx1;
}

int Get_TOUCH_X_MeasureY(void)
{
	FT6336G_RD_Reg(0x00,(unsigned char *)&Touch_Buff,7);

	if ((Touch_Buff[2]&0x01) == 1)
	{
		Pointx1 = (((unsigned int)(Touch_Buff[3] & 0x0F)<<8 | (unsigned int)Touch_Buff[4]));
		Pointy1 = (((unsigned int)(Touch_Buff[5] & 0x0F)<<8 | (unsigned int)Touch_Buff[6]));
		if(Pointy1==0)
			Pointx1=0;	
	}
	else
	{
		Pointy1 =-1;
		Pointx1 =-1;		
	}
	return Pointy1;
}

//FT6336G �䣤?t?��?y?��D???3?��??��
void Touch_Init(void)
{
	unsigned char regdat=0;
	unsigned char ID[2]={0};

  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);

  GPIO_InitStructure.GPIO_Pin = FT_SCL_Pin |FT_SDA_Pin;  //PC4  SDA
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//��?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	

	Touch_IIC_SCL(1);
	Touch_IIC_SDA(1);
	

	regdat=0;FT6336G_WR_Reg(0x00,&regdat,1);
	//2��?��?�꨺?
	regdat=0;FT6336G_WR_Reg(0xA4,&regdat,1);

	//����??����???��
	regdat=22;FT6336G_WR_Reg(0x80,&regdat,1);
	//����?��?��?��   12-14   14��?�䨮
	regdat=14;FT6336G_WR_Reg(0x88,&regdat,1);
  
	FT6336G_RD_Reg(0xA8,ID,1);//D???ID
	FT6336G_RD_Reg(0x00,Touch_Buff,7);
	
}

unsigned char touch(void)
{
	Data_is_ready=1;
	if((Data_is_ready==1)&&(FT6336G_RD_Reg(0x00,Touch_Buff,7)))//��a2??D??2��?���䣤?t���䨬?
	{
		if(Touch_Buff[2]&0x01)
		{
			Pointx1 = 854-(((unsigned int)(Touch_Buff[3] & 0x0F)<<8 | (unsigned int)Touch_Buff[4]));
			Pointy1 = 480-(((unsigned int)(Touch_Buff[5] & 0x0F)<<8 | (unsigned int)Touch_Buff[6]));
			if(Pointx1<0)        Pointx1=0;
			else if(Pointx1>854) Pointx1=854;
			if(Pointy1<0)        Pointy1=0;
			else if(Pointy1>480) Pointy1=480;
			return 1;
		}
		else
	  {
			Pointx1=1;
			Pointy1=1;
	  }
		Data_is_ready=0;
	}
	else
	{
		Pointx1=1;
		Pointy1=1;
	}
	return 0;
}
