#include "stm32f10x.h"
#include "Init.h"

volatile uint16_t tic;
uint8_t MEASURE_STATE = 0;
char buffer_debug [100] = {0};

void TIM1_UP_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET) {
		TIM_Cmd(TIM2, DISABLE);
		tic = TIM_GetCounter(TIM2);
		TIM_SetCounter(TIM2, 0);
		MEASURE_STATE = 1;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		TIM_Cmd(TIM2, ENABLE);
		TIM_Cmd(TIM1, ENABLE);
		}
 }

	
void send_Debug(uint8_t *Data ) {
	while(*Data) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
			; 
			USART_SendData(USART1, *Data++);
	}
}


	int main(void) {

	RCC_AdjustHSICalibrationValue(16);
	RCC_HSEConfig(RCC_HSE_OFF);
	RCC_HSICmd(ENABLE);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA| RCC_APB2Periph_USART1, ENABLE );
		

	USART_Pin_Init();
	USART_Init_Manual();
	TIM1_Master_Init();
	TIM2_ETR_Init();
	TIM1_IT_Update();



	
while(1) {
	if(MEASURE_STATE == 1) {
		MEASURE_STATE = 0;
		snprintf(buffer_debug, 99, "FREQUENCY : %u Hz\r\n", (int)tic); 
		send_Debug((uint8_t*) buffer_debug);

	}
}	
	
}


