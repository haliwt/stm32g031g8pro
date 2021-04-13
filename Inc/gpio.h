/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
#define LEDB8_Pin   						GPIO_PIN_14
#define LEDB8_GPIO_Port 				GPIOC

#define LEDACUT_Pin 						GPIO_PIN_0
#define LEDACUT_GPIO_Port 			GPIOA

#define LEDAPWM_Pin 						GPIO_PIN_1
#define LEDAPWM_GPIO_Port 			GPIOA

#define LEDA1_Pin 							GPIO_PIN_2
#define LEDA1_GPIO_Port 				GPIOA

#define LEDA2_Pin 							GPIO_PIN_3
#define LEDA2_GPIO_Port 				GPIOA

#define LEDA3_Pin 							GPIO_PIN_4
#define LEDA3_GPIO_Port 				GPIOA

#define LEDA4_Pin 							GPIO_PIN_5
#define LEDA4_GPIO_Port 				GPIOA

#define LEDA5_Pin 							GPIO_PIN_6
#define LEDA5_GPIO_Port 				GPIOA

#define LEDA6_Pin 							GPIO_PIN_7
#define LEDA6_GPIO_Port 				GPIOA

#define LEDA7_Pin 							GPIO_PIN_0
#define LEDA7_GPIO_Port 				GPIOB

#define LEDA8_Pin 							GPIO_PIN_1
#define LEDA8_GPIO_Port 				GPIOB

#define FAN_Pin 								GPIO_PIN_8
#define FAN_GPIO_Port 					GPIOA


#define LEDBCUT_Pin 						GPIO_PIN_6
#define LEDBCUT_GPIO_Port 			GPIOC

#define LEDB1_Pin 							GPIO_PIN_11
#define LEDB1_GPIO_Port 				GPIOA

#define LEDB2_Pin 							GPIO_PIN_12
#define LEDB2_GPIO_Port 				GPIOA

#define LEDB3_Pin 							GPIO_PIN_15
#define LEDB3_GPIO_Port 				GPIOA

#define LEDBPWM_Pin 						GPIO_PIN_3
#define LEDBPWM_GPIO_Port 			GPIOB

#define LEDB4_Pin 							GPIO_PIN_4
#define LEDB4_GPIO_Port 				GPIOB

#define LEDB5_Pin 							GPIO_PIN_5
#define LEDB5_GPIO_Port 				GPIOB

//#define LEDB6_Pin								GPIO_PIN_6
//#define LEDB6_GPIO_Port 				GPIOB

#define LEDB7_Pin 							GPIO_PIN_8
#define LEDB7_GPIO_Port 				GPIOB
/* USER CODE BEGIN Private defines */

void MX_GPIO_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
