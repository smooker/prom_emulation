/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

#undef FLASH_ERROR_PG
#undef FLASH_ERROR_WRP
typedef enum
{
    FLASH_BUSY      = HAL_BUSY,
    FLASH_ERROR_PG  = HAL_ERROR,
    FLASH_ERROR_WRP = HAL_ERROR,
    FLASH_COMPLETE  = HAL_OK,
    FLASH_TIMEOUT   = HAL_TIMEOUT
} FLASH_Status;


// Flash Control Register bits
#define CR_PG_Set                ((uint32_t)0x00000001)
#define CR_PG_Reset              ((uint32_t)0x00001FFE)
#define CR_PER_Set               ((uint32_t)0x00000002)
#define CR_PER_Reset             ((uint32_t)0x00001FFD)
#define CR_MER_Set               ((uint32_t)0x00000004)
#define CR_MER_Reset             ((uint32_t)0x00001FFB)
#define CR_OPTPG_Set             ((uint32_t)0x00000010)
#define CR_OPTPG_Reset           ((uint32_t)0x00001FEF)
#define CR_OPTER_Set             ((uint32_t)0x00000020)
#define CR_OPTER_Reset           ((uint32_t)0x00001FDF)
#define CR_STRT_Set              ((uint32_t)0x00000040)
#define CR_LOCK_Set              ((uint32_t)0x00000080)

// Delay definition
#define EraseTimeout          ((uint32_t)0x000B0000)
#define ProgramTimeout        ((uint32_t)0x00002000)

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define BKPT asm("bkpt 255")

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_USER_Pin GPIO_PIN_13
#define LED_USER_GPIO_Port GPIOC
#define SW_RD_EM_Pin GPIO_PIN_14
#define SW_RD_EM_GPIO_Port GPIOC
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOA
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOA
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOA
#define A3_Pin GPIO_PIN_3
#define A3_GPIO_Port GPIOA
#define A4_Pin GPIO_PIN_4
#define A4_GPIO_Port GPIOA
#define A5_Pin GPIO_PIN_5
#define A5_GPIO_Port GPIOA
#define A6_Pin GPIO_PIN_6
#define A6_GPIO_Port GPIOA
#define A7_Pin GPIO_PIN_7
#define A7_GPIO_Port GPIOA
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOB
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOB
#define D10_Pin GPIO_PIN_10
#define D10_GPIO_Port GPIOB
#define D11_Pin GPIO_PIN_11
#define D11_GPIO_Port GPIOB
#define D12_Pin GPIO_PIN_12
#define D12_GPIO_Port GPIOB
#define D13_Pin GPIO_PIN_13
#define D13_GPIO_Port GPIOB
#define D14_Pin GPIO_PIN_14
#define D14_GPIO_Port GPIOB
#define D15_Pin GPIO_PIN_15
#define D15_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOB
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOB
#define D8_Pin GPIO_PIN_8
#define D8_GPIO_Port GPIOB
#define D9_Pin GPIO_PIN_9
#define D9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
