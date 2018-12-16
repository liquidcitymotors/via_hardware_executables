
#include <via_f373_system.hpp>
#include "tsl_user.h"
#include "stm32f3xx_it.h"
#include "interrupt_link.hpp"

#define EXPAND_LOGIC_HIGH GPIOA->BRR = (uint32_t)GPIO_PIN_12;
#define EXPAND_LOGIC_LOW GPIOA->BSRR = (uint32_t)GPIO_PIN_12;


int triggerDebounce;

#ifdef __cplusplus
extern "C" {
#endif

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern TIM_HandleTypeDef htim18;


/*
 *
 *  Logic input interrupts
 *
 */

// Main trigger input

void TIM12_IRQHandler(void)
{

	if (TRIGGER_RISING_EDGE) {
		(*mainRisingEdgeCallback)(modulePointer);
	} else {
		(*mainFallingEdgeCallback)(modulePointer);
	}

	__HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_CC2);

}

// Aux trigger input

void EXTI15_10_IRQHandler(void)
{

	if (EXPANDER_RISING_EDGE) {
		(*auxRisingEdgeCallback)(modulePointer);
	} else {
		(*auxFallingEdgeCallback)(modulePointer);
	}

  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);

}

// Expander button

void EXTI1_IRQHandler(void)
{

	if (EXPANDER_BUTTON_PRESSED) {
		if (!triggerDebounce) {
			//uiDispatch(EXPAND_SW_ON_SIG);
			triggerDebounce = 1;
			__HAL_TIM_ENABLE(&htim16);
			(*buttonPressedCallback)(modulePointer);
		}
	} else { //falling edge
		if (!triggerDebounce) {
			//uiDispatch(EXPAND_SW_OFF_SIG);
			triggerDebounce = 1;
			__HAL_TIM_ENABLE(&htim16);
			(*buttonReleasedCallback)(modulePointer);
		}
	}

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);

}

/*
 *
 * Timer interrputs
 *
 */

// SH A

void TIM16_IRQHandler(void)
{

	triggerDebounce = 0;

	if (!EXPANDER_BUTTON_PRESSED) {
		(*buttonReleasedCallback)(modulePointer);
	}

	__HAL_TIM_CLEAR_FLAG(&htim16, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim16);

}

// SH B

void TIM17_IRQHandler(void)
{

	(*auxTimer1InterruptCallback)(modulePointer);
	TIM18->CR1 |= TIM_CR1_CEN;

	__HAL_TIM_CLEAR_FLAG(&htim17, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim17);

}

void TIM18_DAC2_IRQHandler(void)
{

	(*auxTimer2InterruptCallback)(modulePointer);

	__HAL_TIM_CLEAR_FLAG(&htim18, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim18);

}

// run touch sensor state machine

void TIM13_IRQHandler(void)
{

	int tsl_status_here;
	// run the state machine from the STM Touch Library
	tsl_status_here = tsl_user_Exec();
	__HAL_TIM_CLEAR_FLAG(&htim13, TIM_FLAG_UPDATE);

}

// ui timer

void TIM7_IRQHandler(void)
{


	(*uiTimerCallback)(modulePointer);

	HAL_TIM_IRQHandler(&htim7);

}

/*
 *
 * DMA transfer complete interrupts
 *
 */

// slow ADCs

void DMA1_Channel1_IRQHandler(void)
{

	//EXPAND_LOGIC_HIGH


	//minimal interrupt handler for circular buffer

	if ((DMA1->ISR & (DMA_FLAG_HT1)) != 0) {
		DMA1->IFCR = DMA_FLAG_HT1;
	} else {
		DMA1->IFCR = DMA_FLAG_TC1;
		(*adcConversionCompleteCallback)(modulePointer);
	}

	//EXPAND_LOGIC_LOW

}

void DMA1_Channel5_IRQHandler(void)
{

	//EXPAND_LOGIC_HIGH

	if ((DMA1->ISR & (DMA_FLAG_HT1 << 16)) != 0) {
		DMA1->IFCR = DMA_FLAG_HT1 << 16;
		(*dacHalfTransferCallback)(modulePointer);
	} else if ((DMA1->ISR & (DMA_FLAG_TC1 << 16)) != 0)  {
		DMA1->IFCR = DMA_FLAG_TC1 << 16;
		(*dacTransferCompleteCallback)(modulePointer);
	}

	//EXPAND_LOGIC_LOW

}

#ifdef __cplusplus
}
#endif




