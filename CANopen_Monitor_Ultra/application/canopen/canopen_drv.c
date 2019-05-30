#include "canopen_drv.h"
#include "canopen_app.h"
#include "Master.h"

/* ��ʱ��TIM��ر��� */
static TIMEVAL last_counter_val = 0;
static TIMEVAL elapsed_time = 0;

void CANOpen_Driver_Init(void)
{
	CANOpen_TIM_Configuration();
	CAN_Initializes();
	CANOpen_Node_Init();
}


void CANSend_Date(CanTxMsg TxMsg)
{
	//if(CAN_Transmit(CANx, &TxMsg) == CAN_NO_MB)
	//{
	//	delay_ms(1);                           //��һ�η���ʧ��, ��ʱ1���δ�, �ٴη���
		CAN_Transmit(CANx, &TxMsg);
	//}
}


void CANRcv_DateFromISR(CanRxMsg *RxMsg)
{
	static Message msg;
	uint8_t i = 0;
	msg.cob_id = RxMsg->StdId;                  //CAN-ID

	if(CAN_RTR_REMOTE == RxMsg->RTR)
		msg.rtr = 1;                             //Զ��֡
	else
		msg.rtr = 0;                             //����֡

	msg.len = (UNS8)RxMsg->DLC;                 //����

	for(i=0; i<RxMsg->DLC; i++)                 //����
		msg.data[i] = RxMsg->Data[i];

	TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, DISABLE);

	canDispatch(&Master_Data, &msg);       //����Э����ؽӿ�

	TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, ENABLE);
}


/********************************** CANOpen�ӿں���(���Լ�ʵ��) **********************************/
/************************************************
�������� �� canSend
��    �� �� CAN����
��    �� �� notused --- δʹ�ò���
            m --------- ��Ϣ����
�� �� ֵ �� 0:ʧ��  1:�ɹ�
*************************************************/
unsigned char canSend(CAN_PORT notused, Message *m)
{
  uint8_t i;
  static CanTxMsg TxMsg;
	
  TxMsg.StdId = m->cob_id;

  if(m->rtr)
      TxMsg.RTR = CAN_RTR_REMOTE;
  else
      TxMsg.RTR = CAN_RTR_DATA;

  TxMsg.IDE = CAN_ID_STD;
  TxMsg.DLC = m->len;
  for(i=0; i<m->len; i++)
      TxMsg.Data[i] = m->data[i];

  CANSend_Date(TxMsg);

  return 0;
}

/************************************************
�������� �� setTimer
��    �� �� Set the timer for the next alarm.
��    �� �� value --- ����
�� �� ֵ �� ��
*************************************************/
void setTimer(TIMEVAL value)
{
//  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

//  elapsed_time += timer - last_counter_val;
//  last_counter_val = CANOPEN_TIM_PERIOD - value;
//  TIM_SetCounter(CANOPEN_TIMx, CANOPEN_TIM_PERIOD - value);
//  TIM_Cmd(CANOPEN_TIMx, ENABLE);
//	
	TIM_SetAutoreload(CANOPEN_TIMx, value);// ����һ����������ܲ��ܳ�
}

/************************************************
�������� �� getElapsedTime
��    �� �� Return the elapsed time to tell the Stack how much time is spent since last call.
��    �� �� ��
�� �� ֵ �� (���ŵ�)ʱ��
*************************************************/
TIMEVAL getElapsedTime(void)
{
  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

  if(timer < last_counter_val)
    timer += CANOPEN_TIM_PERIOD;

  TIMEVAL elapsed = timer - last_counter_val + elapsed_time;

  return elapsed;
}

/************************************************
�������� �� TIMx_DispatchFromISR
��    �� �� ��ʱ����(�Ӷ�ʱ���ж�)
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void TIMx_DispatchFromISR(void)
{
  last_counter_val = 0;
  elapsed_time = 0;
  TimeDispatch();
}
