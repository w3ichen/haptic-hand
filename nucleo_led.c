#include "nucleo_led.h"
#include "stm32f446ze_gpio.h"
#include "stm32f4xx_rcc_mort.h"


GPIOInitTypeDef ledgpioinitstruct;

void initLED1 (void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    ledgpioinitstruct.GPIO_Mode = GPIOModeOUT;
    ledgpioinitstruct.GPIO_OType = GPIOOTypePP;
    ledgpioinitstruct.GPIO_Speed = GPIOLowSpeed;
    ledgpioinitstruct.GPIO_PuPd = GPIOPuPdNOPULL;
    ledgpioinitstruct.GPIO_Pin = GPIOPin0;
    GPIOInit((GPIOTypeDef *)GPIOB_BASE_MORT, &ledgpioinitstruct);
}

void toggleLED1 (void)
{
    GPIOToggleBits((GPIOTypeDef *)GPIOB_BASE_MORT, (uint16_t)GPIOPin0);
}

void turnLED1ON (void)
{
    GPIOSetBits((GPIOTypeDef *)GPIOB_BASE_MORT, (uint16_t)GPIOPin0);
}

void turnLED1OFF(void)
{
    GPIOClearBits((GPIOTypeDef *)GPIOB_BASE_MORT, (uint16_t)GPIOPin0);
}
