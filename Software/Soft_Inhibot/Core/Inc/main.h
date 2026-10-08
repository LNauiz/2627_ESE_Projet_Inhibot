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
#include "stm32g4xx_hal.h"

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
#define TOF2_XST_Pin GPIO_PIN_14
#define TOF2_XST_GPIO_Port GPIOC
#define TOF2_GPIO_Pin GPIO_PIN_15
#define TOF2_GPIO_GPIO_Port GPIOC
#define TIM_RGB_Pin GPIO_PIN_0
#define TIM_RGB_GPIO_Port GPIOC
#define INT_Color_Pin GPIO_PIN_2
#define INT_Color_GPIO_Port GPIOC
#define FAULT_Pin GPIO_PIN_3
#define FAULT_GPIO_Port GPIOC
#define PWM_Driver_1_Pin GPIO_PIN_0
#define PWM_Driver_1_GPIO_Port GPIOA
#define PWM_Driver_2_Pin GPIO_PIN_1
#define PWM_Driver_2_GPIO_Port GPIOA
#define Prog_Tx_Pin GPIO_PIN_2
#define Prog_Tx_GPIO_Port GPIOA
#define Prog_Rx_Pin GPIO_PIN_3
#define Prog_Rx_GPIO_Port GPIOA
#define PWM_Servo_Pin GPIO_PIN_6
#define PWM_Servo_GPIO_Port GPIOA
#define PWM_Servo2_Pin GPIO_PIN_7
#define PWM_Servo2_GPIO_Port GPIOA
#define QON_Pin GPIO_PIN_0
#define QON_GPIO_Port GPIOB
#define PWM_Driver_3_Pin GPIO_PIN_10
#define PWM_Driver_3_GPIO_Port GPIOB
#define PWM_Driver_4_Pin GPIO_PIN_11
#define PWM_Driver_4_GPIO_Port GPIOB
#define TOF1_GPIO_Pin GPIO_PIN_13
#define TOF1_GPIO_GPIO_Port GPIOB
#define TOF1_XST_Pin GPIO_PIN_14
#define TOF1_XST_GPIO_Port GPIOB
#define ENCODER1_CH2_Pin GPIO_PIN_6
#define ENCODER1_CH2_GPIO_Port GPIOC
#define ENCODER1_CH1_Pin GPIO_PIN_7
#define ENCODER1_CH1_GPIO_Port GPIOC
#define BMS_INT_Pin GPIO_PIN_9
#define BMS_INT_GPIO_Port GPIOC
#define BATTERY_I2C_SDA_Pin GPIO_PIN_8
#define BATTERY_I2C_SDA_GPIO_Port GPIOA
#define BATTERY_I2C_SCL_Pin GPIO_PIN_9
#define BATTERY_I2C_SCL_GPIO_Port GPIOA
#define LED_STATUS_Pin GPIO_PIN_10
#define LED_STATUS_GPIO_Port GPIOA
#define ESP32_TX_Pin GPIO_PIN_10
#define ESP32_TX_GPIO_Port GPIOC
#define ESP32_RX_Pin GPIO_PIN_11
#define ESP32_RX_GPIO_Port GPIOC
#define INT1_Mag_Pin GPIO_PIN_4
#define INT1_Mag_GPIO_Port GPIOB
#define INT2_Mag_Pin GPIO_PIN_5
#define INT2_Mag_GPIO_Port GPIOB
#define ENCODER2_CH1_Pin GPIO_PIN_6
#define ENCODER2_CH1_GPIO_Port GPIOB
#define ENCODER2_CH2_Pin GPIO_PIN_7
#define ENCODER2_CH2_GPIO_Port GPIOB
#define SENSOR_I2C_SCL_Pin GPIO_PIN_8
#define SENSOR_I2C_SCL_GPIO_Port GPIOB
#define SENSOR_I2C_SDA_Pin GPIO_PIN_9
#define SENSOR_I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
