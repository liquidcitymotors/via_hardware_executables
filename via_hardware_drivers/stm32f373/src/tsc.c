/**
 ******************************************************************************
 * File Name          : TSC.c
 * Description        : This file provides code for the configuration
 *                      of the TSC instances.
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether 
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V. 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other 
 *    contributors to this software may be used to endorse or promote products 
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this 
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under 
 *    this license is void and will automatically terminate your rights under 
 *    this license. 
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tsc.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TSC_HandleTypeDef htsc;

/* TSC init function */
void MX_TSC_Init(void) {

	/**Configure the TSC peripheral 
	 */
	htsc.Instance = TSC;
	htsc.Init.CTPulseHighLength = TSC_CTPH_5CYCLES;
	htsc.Init.CTPulseLowLength = TSC_CTPL_5CYCLES;
	htsc.Init.SpreadSpectrum = DISABLE;
	htsc.Init.SpreadSpectrumDeviation = 1;
	htsc.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
	htsc.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV4;
	htsc.Init.MaxCountValue = TSC_MCV_8191;
	htsc.Init.IODefaultMode = TSC_IODEF_OUT_PP_LOW;
	htsc.Init.SynchroPinPolarity = TSC_SYNC_POLARITY_FALLING;
	htsc.Init.AcquisitionMode = TSC_ACQ_MODE_NORMAL;
	htsc.Init.MaxCountInterrupt = DISABLE;
	htsc.Init.ChannelIOs = TSC_GROUP4_IO2 | TSC_GROUP5_IO2 | TSC_GROUP5_IO3
			| TSC_GROUP5_IO4 | TSC_GROUP6_IO2 | TSC_GROUP6_IO3;
	htsc.Init.ShieldIOs = 0;
	htsc.Init.SamplingIOs = TSC_GROUP4_IO1 | TSC_GROUP5_IO2 | TSC_GROUP6_IO1;
	if (HAL_TSC_Init(&htsc) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

void HAL_TSC_MspInit(TSC_HandleTypeDef* tscHandle) {

	GPIO_InitTypeDef GPIO_InitStruct;
	if (tscHandle->Instance == TSC) {
		/* USER CODE BEGIN TSC_MspInit 0 */

		/* USER CODE END TSC_MspInit 0 */
		/* TSC clock enable */
		__HAL_RCC_TSC_CLK_ENABLE()
		;

		/**TSC GPIO Configuration    
		 PB14     ------> TSC_G6_IO1
		 PB15     ------> TSC_G6_IO2
		 PD8     ------> TSC_G6_IO3
		 PA9     ------> TSC_G4_IO1
		 PA10     ------> TSC_G4_IO2
		 PB3     ------> TSC_G5_IO1
		 PB4     ------> TSC_G5_IO2
		 PB6     ------> TSC_G5_IO3
		 PB7     ------> TSC_G5_IO4 
		 */
		GPIO_InitStruct.Pin = GROUP_6_SAMPLING_Pin | GPIO_PIN_4;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin =
				GPIO_PIN_15 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GROUP_4_SAMPLING_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
		HAL_GPIO_Init(GROUP_4_SAMPLING_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN TSC_MspInit 1 */

		/* USER CODE END TSC_MspInit 1 */
	}
}

void HAL_TSC_MspDeInit(TSC_HandleTypeDef* tscHandle) {

	if (tscHandle->Instance == TSC) {
		/* USER CODE BEGIN TSC_MspDeInit 0 */

		/* USER CODE END TSC_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_TSC_CLK_DISABLE();

		/**TSC GPIO Configuration    
		 PB14     ------> TSC_G6_IO1
		 PB15     ------> TSC_G6_IO2
		 PD8     ------> TSC_G6_IO3
		 PA9     ------> TSC_G4_IO1
		 PA10     ------> TSC_G4_IO2
		 PB3     ------> TSC_G5_IO1
		 PB4     ------> TSC_G5_IO2
		 PB6     ------> TSC_G5_IO3
		 PB7     ------> TSC_G5_IO4 
		 */
		HAL_GPIO_DeInit(GPIOB,
				GROUP_6_SAMPLING_Pin | GPIO_PIN_15 | GPIO_PIN_3 | GPIO_PIN_4
						| GPIO_PIN_6 | GPIO_PIN_7);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8);

		HAL_GPIO_DeInit(GPIOA, GROUP_4_SAMPLING_Pin | GPIO_PIN_10);

		/* USER CODE BEGIN TSC_MspDeInit 1 */

		/* USER CODE END TSC_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
