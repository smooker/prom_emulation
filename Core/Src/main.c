/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdint.h"
#include "core_cm3.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

/* USER CODE BEGIN PV */

uint32_t pageStartAddr = 0x0800F000;        //fixme. da si go vzeme ot linkera

uint16_t arrRam[256];
uint16_t arrRamOld[256];            //just for debug. fixme later

uint32_t crcOld = 0;
uint32_t crcNew = 0;
uint32_t iteration = 0;

__attribute__((section(".romdata"))) const uint16_t arrFlash[256] = {
    0xcd74,  0x5edc,  0xcd74,  0x5edc,  0xcf64,  0x5edb,  0xcf74,  0x5eda,  0xcf74,  0x5eda,
    0xcf74,  0x5eda,  0xcf74,  0x5eda,  0xcf74,  0x5eda,  0x5de5,  0x57cc,  0x5df5,  0x57cb,
    0x5fe5,  0x57ca,  0x5ff5,  0x57c9,  0x5ded,  0x57ab,  0x5dfd,  0x57aa,  0x5fed,  0x57a9,
    0x5ffd,  0x57a8,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,
    0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0x5de4,  0x57af,
    0x5df4,  0x57ae,  0x5fe4,  0x57ad,  0x5ff4,  0x57ac,  0x5dec,  0x57ab,  0x5dfc,  0x57aa,
    0x5fec,  0x57a9,  0x5ffc,  0x57a8,  0xd9c5,  0x97cb,  0xd9d5,  0x97ca,  0xdbc5,  0x97ac,
    0xdbd5,  0x97ab,  0xd9cd,  0x97aa,  0xd9dd,  0x97a9,  0xdbcd,  0x97a8,  0xdbdd,  0x97a7,
    0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,
    0xdd2f,  0xe208,  0xdd2f,  0xe208,  0xdd2f,  0xe208,  0x5df5,  0xf00f,  0x5fe5,  0xf00e,
    0x5ff5,  0xf00d,  0x5ded,  0xf00c,  0x5dfd,  0xf00b,  0x5fed,  0xf00a,  0x5ffd,  0xf009,
    0x7fbd,  0xf208,  0x7e24,  0xdbd9,  0x7e34,  0xdbda,  0x7c2c,  0xdbdb,  0x7c3c,  0xdba9,
    0x7e2c,  0xdbaa,  0x7e3c,  0xdbab,  0x7ebc,  0xfb99,  0x7e1d,  0xfb9a,  0x5575,  0x798e,
    0x5765,  0x798d,  0x5775,  0x798c,  0x556d,  0x798b,  0x557d,  0x798a,  0x576d,  0x7989,
    0x577d,  0x799b,  0x7f1d,  0x7b9a,  0x7f24,  0x5bd9,  0x7f34,  0x5bda,  0x7d2c,  0x5bdb,
    0x7d3c,  0x5ba9,  0x7f2c,  0x5baa,  0x7f3c,  0x5bab,  0x7fbc,  0x7b99,  0x7f1d,  0x7b9a,
    0xee3c,  0xf20c,  0xee3c,  0xf20c,  0xee3c,  0xf20c,  0xee3c,  0xf20c,  0xee3c,  0xf20c,
    0xee3c,  0xf20c,  0xee3c,  0xf20c,  0xee3c,  0xf20c,  0xdd65,  0x17cc,  0xdd75,  0x17cb,
    0xdf65,  0x17ca,  0xdf75,  0x17c9,  0xdd6d,  0x17ab,  0xdd7d,  0x17aa,  0xdf6d,  0x17a9,
    0xdf7d,  0x17a8,  0xcd74,  0x719d,  0xcf64,  0x719c,  0xcf74,  0x719b,  0xcd6c,  0x71ad,
    0xcd7c,  0x71ac,  0xcf6c,  0x71ab,  0xcf7c,  0x700d,  0xef3c,  0x720c,  0x5d16,  0xd38a,
    0x5f06,  0xd3a8,  0x5f16,  0xd3a9,  0x5d0e,  0xd3aa,  0x5d1e,  0xd3c8,  0x5f0e,  0xd3c9,
    0x5f1e,  0xd3ca,  0xdd2f,  0xe208,  0x5d16,  0xf18a,  0x5f06,  0xf1a8,  0x5f16,  0xf1a9,
    0x5d0e,  0xf1aa,  0x5d1e,  0xf1c8,  0x5f0e,  0xf1c9,  0x5f1e,  0xf1ca,  0xdd2f,  0xf208,
    0x5d16,  0xe38a,  0x5f06,  0xe3a8,  0x5f16,  0xe3a9,  0x5d0e,  0xe3aa,  0x5d1e,  0xe3c8,
    0x5f0e,  0xe3c9,  0x5f1e,  0xe3ca,  0xdd2f,  0xe208};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
/* USER CODE BEGIN PFP */

void readFlash2Ram();
void fillRam();
void readProm2Ram();
void emulateProm();
static void GPIO2Emul(void);
void copyArrRam2ArrRamOld();

static FLASH_Status writeRam2Flash();
static FLASH_Status FLASH_ErasePage(uint32_t Page_Address);

//
uint16_t FLASH_Unlock()
{
    uint16_t Status = HAL_FLASH_Unlock();      //fixme. move the same into ee_init and into ww_writevariable
    assert_param(Status == HAL_OK);
    if(Status != HAL_OK) {
        BKPT;
    };
    return Status;
}

//fixme add flash_lock

void copyArrRam2ArrRamOld()
{
    uint8_t index = 0;

    while(1) {
        arrRamOld[index]  = arrRam[index];
        index++;
        if ( index == 0) {
            break;
        }
    }
}

//
static FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Page_Address));

    status = (FLASH_Status) FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CR|= CR_PER_Set;
        FLASH->AR = Page_Address;
        FLASH->CR|= CR_STRT_Set;

        /* Wait for last operation to be completed */
        status = (FLASH_Status) FLASH_WaitForLastOperation(EraseTimeout);
        /* Disable the PER Bit */
        FLASH->CR &= CR_PER_Reset;
        // BKPT; //SUCCESS ERASE
    }
    // BKPT;   //COMMON BKPT
    return status;
}

////
void fillRam()
{
    uint8_t addr = 0;
    while (1) {
        arrRam[addr] = 0x55aa;
        addr++;
        if (addr == 0) {
            break;
        }
    }
}

// Address increment and reads B0-B15 into arrRam
void readProm2Ram()
{
    uint8_t addr = 0;
    uint32_t addr32 =0;
    while (1) {
        // send to A0-A7
        addr32 =  (~(addr & 0x00ff) << 16u) | (addr & 0x00ff);
        GPIOA->BSRR = addr32;

        // easy
        HAL_Delay(0);            //fixme

        //read whole 16 bits into arr
        arrRam[addr] = (uint16_t)GPIOB->IDR & 0x0000ffff;
        // if ( arrRam[addr] > 0x00 ) {
        //     BKPT;
        // }
        addr++;
        if (addr == 0) {
            break;
        }
    }
    // BKPT; // ROM IS IN RAM
}

// emulate prom
void emulateProm()
{
    while (1) {
        uint32_t data32;

        uint16_t data16;

        uint8_t addr = (uint16_t)GPIOA->IDR & 0x000000ff;

        // data16 = arrFlash[addr];
        data16 = arrRam[addr];

        data32 =  (~(data16 & 0xffff) << 16u) | (data16 & 0xffff);
        GPIOB->BSRR = data32;

        // BKPT;
    }
}

// reads ROM from FLASH to RAM
void readFlash2Ram()
{
    //
    uint8_t cnt = 0;
    uint16_t value;
    while(1) {
        value = (*(__IO uint16_t*)(pageStartAddr+2*cnt));
        arrRam[cnt] = value;
        cnt++;
        if (cnt == 0) {
            break;
        }
    }
    // BKPT;   // FLASHROM IS IN RAM
}

static FLASH_Status writeRam2Flash()
{
    FLASH_Status FlashStatus = FLASH_COMPLETE;

    uint32_t Address;
    uint8_t index = 0;

    while(1) {
        Address = pageStartAddr+(index*2);
        if ((*(__IO uint32_t*)Address) == 0xFFFFFFFF)
        {
            /* Wait for last operation to be completed */
            FlashStatus = (FLASH_Status) FLASH_WaitForLastOperation(ProgramTimeout);

            if(FlashStatus == FLASH_COMPLETE)
            {
                /* if the previous operation is completed, proceed to program the new data */
                FLASH->CR |= CR_PG_Set;

                *(__IO uint16_t*)Address = arrRam[index];
                /* Wait for last operation to be completed */
                FlashStatus = (FLASH_Status) FLASH_WaitForLastOperation(ProgramTimeout);

                /* Disable the PG Bit */
                FLASH->CR &= CR_PG_Reset;
            }

            /* If program operation was failed, a Flash error code is returned */
            if (FlashStatus != FLASH_COMPLETE)
            {
                // FLASH_Status FlashStatus2 = FlashStatus;
                BKPT;   // ERROR WRITING TO FLASH
            }
        } else {
            BKPT;   // HAS NOT BEEN ERASED
        }
        index++;
        if (index == 0) {
            break;
        }
    }
    return FlashStatus;
}

uint32_t crcCalcOfarrRam() {
    uint32_t crc_val = HAL_CRC_Calculate(&hcrc, (uint32_t*)arrRam, 128);
    return crc_val;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define SW_RD_EM_RESET  (HAL_GPIO_ReadPin(SW_RD_EM_GPIO_Port, SW_RD_EM_Pin) == GPIO_PIN_RESET)
#define SW_RD_EM_SET    (HAL_GPIO_ReadPin(SW_RD_EM_GPIO_Port, SW_RD_EM_Pin) == GPIO_PIN_SET)

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);

  // FLASH_Unlock();
  // BKPT;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  __HAL_RCC_CRC_CLK_ENABLE();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  // fillRam();
  // BKPT;

  // readArrFromProm();
  // BKPT;

  // FLASH_ErasePage(pageStartAddr);
  // BKPT;

  // writeRam2Flash();
  // BKPT;

  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
  HAL_Delay(300);
  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_SET);
  HAL_Delay(300);
  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
  HAL_Delay(300);

  if ( SW_RD_EM_SET ) {
        // here goes emulation
        GPIO2Emul();
        readFlash2Ram();
        emulateProm();
  }

  if ( SW_RD_EM_RESET ) {
        // here goes reading of prom
        uint8_t i = 2;
        while (i-- > 0 )
        {
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
            HAL_Delay(500);
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_SET);
            HAL_Delay(500);
        }

        //actual reading
        i = 100;
        while (i-- > 0) {
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_SET);
            HAL_Delay(200);

            readProm2Ram();
            crcNew = crcCalcOfarrRam();
            if ( (crcOld != 0x0) & (crcOld != crcNew) ) {
                BKPT;
            }
            copyArrRam2ArrRamOld();
            crcOld = crcNew;
            iteration++;
        }

        while ( SW_RD_EM_RESET ) {
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
            HAL_Delay(20);
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_SET);
            HAL_Delay(20);
        }
        // to flash
        FLASH_Unlock();
        FLASH_ErasePage(pageStartAddr);
        i = 3;
        while (i-- > 0 )
        {
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
            HAL_Delay(500);
            HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_SET);
            HAL_Delay(500);
        }
        writeRam2Flash();
        HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A0_Pin|A1_Pin|A2_Pin|A3_Pin
                          |A4_Pin|A5_Pin|A6_Pin|A7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_USER_Pin */
  GPIO_InitStruct.Pin = LED_USER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_USER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_RD_EM_Pin */
  GPIO_InitStruct.Pin = SW_RD_EM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_RD_EM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : A0_Pin A1_Pin A2_Pin A3_Pin
                           A4_Pin A5_Pin A6_Pin A7_Pin */
  GPIO_InitStruct.Pin = A0_Pin|A1_Pin|A2_Pin|A3_Pin
                          |A4_Pin|A5_Pin|A6_Pin|A7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D10_Pin
                           D11_Pin D12_Pin D13_Pin D14_Pin
                           D15_Pin D3_Pin D4_Pin D5_Pin
                           D6_Pin D7_Pin D8_Pin D9_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D10_Pin
                          |D11_Pin|D12_Pin|D13_Pin|D14_Pin
                          |D15_Pin|D3_Pin|D4_Pin|D5_Pin
                          |D6_Pin|D7_Pin|D8_Pin|D9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


static void GPIO2Emul(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_USER_GPIO_Port, LED_USER_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOB, D0_Pin|D1_Pin|D2_Pin|D3_Pin|D4_Pin|D5_Pin|D6_Pin|D7_Pin
                               |D8_Pin|D9_Pin|D10_Pin|D11_Pin|D12_Pin|D13_Pin|D14_Pin|D15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_USER_Pin */
  GPIO_InitStruct.Pin = LED_USER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_USER_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SW_RD_EM_Pin */
  GPIO_InitStruct.Pin = SW_RD_EM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW_RD_EM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : A0_Pin A1_Pin A2_Pin A3_Pin
                           A4_Pin A5_Pin A6_Pin A7_Pin */
  GPIO_InitStruct.Pin = A0_Pin|A1_Pin|A2_Pin|A3_Pin
                        |A4_Pin|A5_Pin|A6_Pin|A7_Pin;

  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin D2_Pin D10_Pin
                           D11_Pin D12_Pin D13_Pin D14_Pin
                           D15_Pin D3_Pin D4_Pin D5_Pin
                           D6_Pin D7_Pin D8_Pin D9_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin|D2_Pin|D10_Pin
                        |D11_Pin|D12_Pin|D13_Pin|D14_Pin
                        |D15_Pin|D3_Pin|D4_Pin|D5_Pin
                        |D6_Pin|D7_Pin|D8_Pin|D9_Pin;

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
