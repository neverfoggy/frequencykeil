#include "stm32f10x.h"
#include "Init.h"


GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TIM_1_Master, TIM_2_ETR, TIM_3_ITR1 ;

void TIM1_Master_Init(void) {
	
	TIM_1_Master.TIM_Prescaler = 799;
	TIM_1_Master.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_1_Master.TIM_Period = 9999;
	TIM_1_Master.TIM_RepetitionCounter = 0;
	TIM_1_Master.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_ARRPreloadConfig(TIM1, DISABLE);
	TIM_InternalClockConfig(TIM1);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);	 
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
	TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Single);	
	TIM_TimeBaseInit(TIM1, &TIM_1_Master);	
	TIM_Cmd(TIM1,ENABLE);
	TIM1_IT_Update();
}

void TIM2_ETR_Init(void) {
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM_2_ETR.TIM_Prescaler = 0; 
	TIM_2_ETR.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_2_ETR.TIM_Period = 65535;
	TIM_2_ETR.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);
	TIM_ITRxExternalClockConfig(TIM2, TIM_TS_ITR0);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Disable);
	
	TIM_TimeBaseInit(TIM2, &TIM_2_ETR);
	TIM_Cmd(TIM2, ENABLE);
	
}

/*void TIM3_ITR1_Init(void) {
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3, ENABLE);
	TIM_3_ITR1.TIM_Prescaler = 0; 
	TIM_3_ITR1.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_3_ITR1.TIM_Period = 65535;
	TIM_3_ITR1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_ARRPreloadConfig(TIM3, DISABLE);
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_External1);
	TIM_ITRxExternalClockConfig(TIM3, TIM_TS_ITR1);
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Reset);	
	TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Disable);
	TIM_TimeBaseInit(TIM3, &TIM_3_ITR1);
	TIM_Cmd(TIM3,ENABLE);
  		
}

void MCO_Init(void) {
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_MCOConfig(RCC_MCO_HSI);
}	
*/

void TIM1_IT_Update(void) {
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	NVIC_InitTypeDef nvicStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	nvicStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);	
}

void USART_Pin_Init(void) {
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void USART_Init_Manual(void) {
	USART_InitTypeDef USART_InitStructure; 
	USART_InitStructure.USART_BaudRate = 115200; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
	USART_Init(USART1, &USART_InitStructure); 
	USART_Cmd(USART1, ENABLE); 
}

