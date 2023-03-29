/**
 ******************************************************************************
 * @file    6283a1_conf.h
 * @author  IMG SW Application Team
 * @brief   This file contains definitions for the ALS components bus interfaces
 *          when using the X-NUCLEO-6283A1 expansion board
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

#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo_bus.h"
#include "stm32l4xx_nucleo_errno.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __6283A1_CONF_H__
#define __6283A1_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#define LIGHT_SENSOR_INSTANCES_NBR      (1U)

#define VD6283A1_I2C_SCL_GPIO_PORT      BUS_I2C1_SCL_GPIO_PORT
#define VD6283A1_I2C_SCL_GPIO_PIN       BUS_I2C1_SCL_GPIO_PIN
#define VD6283A1_I2C_SDA_GPIO_PORT      BUS_I2C1_SDA_GPIO_PORT
#define VD6283A1_I2C_SDA_GPIO_PIN       BUS_I2C1_SDA_GPIO_PIN

#define VD6283A1_I2C_Init               BSP_I2C1_Init
#define VD6283A1_I2C_DeInit             BSP_I2C1_DeInit
#define VD6283A1_I2C_WriteReg           BSP_I2C1_WriteReg
#define VD6283A1_I2C_ReadReg            BSP_I2C1_ReadReg
#define VD6283A1_GetTick                BSP_GetTick

#ifdef __cplusplus
}
#endif

#endif /* __6283A1_CONF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
