/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2s.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint16_t PCM_rx_buf[128];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
    {
//    LD3_GPIO_Port->ODR &= ~ LD3_Pin;
//    HAL_Delay(1);
    if ((PCM_rx_buf[0] != 0) || (PCM_rx_buf[1] != 0))
	{
	LD3_GPIO_Port->ODR ^= LD3_Pin;
	}
//    volatile uint32_t val = PCM_rx_buf[0];

//    if (val > 2000)
//	{
//	LD3_GPIO_Port->ODR |= LD3_Pin;
//	}
    }
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
volatile u16 dat = 0;
LCD_str LCD1;
LCD_str LCD2;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
    {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();

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
    MX_DMA_Init();
    MX_USART3_UART_Init();
    MX_I2S3_Init();
    MX_SPI4_Init();
    MX_SPI5_Init();
    /* USER CODE BEGIN 2 */
    LCD1.LCD_blk_pin = LCD_BLK_Pin;
    LCD1.LCD_dc_pin = LCD_DC_Pin;
    LCD1.LCD_res_pin = LCD_RES_Pin;
    LCD1.LCD_blk_port = LCD_BLK_GPIO_Port;
    LCD1.LCD_dc_port = LCD_DC_GPIO_Port;
    LCD1.LCD_res_port = LCD_RES_GPIO_Port;
    LCD1.spi_str = &hspi4;

    LCD2.LCD_blk_pin = LCD2_BLK_Pin;
    LCD2.LCD_dc_pin = LCD2_DC_Pin;
    LCD2.LCD_res_pin = LCD2_RES_Pin;
    LCD2.LCD_blk_port = LCD2_BLK_GPIO_Port;
    LCD2.LCD_dc_port = LCD2_DC_GPIO_Port;
    LCD2.LCD_res_port = LCD2_RES_GPIO_Port;
    LCD2.spi_str = &hspi5;
    HAL_Delay(100);
    ST7789_Init(&LCD1);
    HAL_Delay(500);
    ST7789_Init(&LCD2);
//  SPI3->I2SCFGR |= SPI_I2SCFGR_CKPOL;
    //HAL_I2S_Receive_DMA(&hi2s3,&PCM_rx_buf[0], 128);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    u16 i = 1;
    while (1)
	{
//	HAL_I2S_Receive(&hi2s3, &PCM_rx_buf[0], sizeof(PCM_rx_buf), 0xFF);
//	for (u16 i = 0; i < 128; i++)
//	    {
//	    if (PCM_rx_buf[i] != 0)
//		{
//		dat = PCM_rx_buf[i];
//		LD3_GPIO_Port->ODR |= LD3_Pin;
//		}
//	    }
	switch (i)
	    {
	case 1:
	    i = 2;
	    ST7789_FillScreen(RGB565(0xFF, 0, 0), &LCD1);
	    // HAL_Delay(500);
	    ST7789_FillScreen(RGB565(0xFF, 0, 0), &LCD2);
	    HAL_Delay(500);
	    break;
	case 2:
	    i = 3;
	    ST7789_FillScreen(RGB565(0, 0xFF, 0), &LCD1);
	    // HAL_Delay(500);
	    ST7789_FillScreen(RGB565(0, 0xFF, 0), &LCD2);
	    HAL_Delay(500);
	    break;
	case 3:
	    i = 4;
	    ST7789_FillScreen(RGB565(0, 0, 0xFF), &LCD1);
	    //HAL_Delay(500);
	    ST7789_FillScreen(RGB565(0, 0, 0xFF), &LCD2);
	    HAL_Delay(500);
	    break;
	case 4:
	    i = 1;
	    ST7789_FillScreen(RGB565(0, 0xFF, 0xFF), &LCD1);
	    //   HAL_Delay(500);
	    ST7789_FillScreen(RGB565(0, 0xFF, 0xFF), &LCD2);
	    HAL_Delay(500);
	    break;
	default:
	    break;
	    }

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
    RCC_OscInitTypeDef RCC_OscInitStruct =
	{
	0
	};
    RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{
	0
	};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct =
	{
	0
	};

    /** Supply configuration update enable
     */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    /** Configure the main internal regulator output voltage
     */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY))
	{
	}
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 120;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 | RCC_CLOCKTYPE_D3PCLK1
	    | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
	{
	Error_Handler();
	}
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3
	    | RCC_PERIPHCLK_SPI5 | RCC_PERIPHCLK_SPI4 | RCC_PERIPHCLK_SPI3;
    PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
    PeriphClkInitStruct.Spi45ClockSelection = RCC_SPI45CLKSOURCE_D2PCLK1;
    PeriphClkInitStruct.Usart234578ClockSelection =
    RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
    }

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
    {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/