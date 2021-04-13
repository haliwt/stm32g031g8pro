/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LEDACON_Pin GPIO_PIN_0
#define LEDACON_GPIO_Port GPIOA
#define LEDAPWM_Pin GPIO_PIN_1
#define LEDAPWM_GPIO_Port GPIOA
#define LEDA1_Pin GPIO_PIN_2
#define LEDA1_GPIO_Port GPIOA
#define LEDA2_Pin GPIO_PIN_3
#define LEDA2_GPIO_Port GPIOA
#define LEDA3_Pin GPIO_PIN_4
#define LEDA3_GPIO_Port GPIOA
#define LEDA4_Pin GPIO_PIN_5
#define LEDA4_GPIO_Port GPIOA
#define LEDA5_Pin GPIO_PIN_6
#define LEDA5_GPIO_Port GPIOA
#define LEDA6_Pin GPIO_PIN_7
#define LEDA6_GPIO_Port GPIOA
#define LEDA7_Pin GPIO_PIN_0
#define LEDA7_GPIO_Port GPIOB
#define LEDA8_Pin GPIO_PIN_1
#define LEDA8_GPIO_Port GPIOB
#define FAN_Pin GPIO_PIN_8
#define FAN_GPIO_Port GPIOA
#define LEDBCON_Pin GPIO_PIN_6
#define LEDBCON_GPIO_Port GPIOC
#define LEDB1_Pin GPIO_PIN_11
#define LEDB1_GPIO_Port GPIOA
#define LEDB2_Pin GPIO_PIN_12
#define LEDB2_GPIO_Port GPIOA
#define LEDB3_Pin GPIO_PIN_15
#define LEDB3_GPIO_Port GPIOA
#define LEDBPWM_Pin GPIO_PIN_3
#define LEDBPWM_GPIO_Port GPIOB
#define LEDB4_Pin GPIO_PIN_4
#define LEDB4_GPIO_Port GPIOB
#define LEDB5_Pin GPIO_PIN_5
#define LEDB5_GPIO_Port GPIOB
#define USART1_TX_Pin GPIO_PIN_6
#define USART1_TX_GPIO_Port GPIOB
#define USART1_RX_Pin GPIO_PIN_7
#define USART1_RX_GPIO_Port GPIOB
#define LEDB7_Pin GPIO_PIN_8
#define LEDB7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
