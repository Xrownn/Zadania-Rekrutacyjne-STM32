#pragma once
#include "main.h"
#include "stm32g4xx_hal.h"

void spx25_set_mode(GPIO_PinState ctrl0, GPIO_PinState ctrl1);
void spx25_measurement_conversion(uint8_t selected_mode,uint16_t value);
