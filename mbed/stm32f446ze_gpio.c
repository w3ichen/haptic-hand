#include "stm32f446ze_gpio.h"
#include "debug_mort.h"

#define PORTB_BASE_ADDRESS ((uint32_t)0x40020400)
#define PORTB_MODER_REGISTER (PORTB_BASE_ADDRESS + 0x00)

//Initializes one gpio pin at a time.
void GPIOInit(GPIOTypeDef * gpiox, GPIOInitTypeDef * gpioinit)
{
    uint8_t pinpos;
    uint32_t  * reg_pointer;
    uint32_t pin;
      
    pinpos = 0;

    
    pin = (gpioinit->GPIO_Pin)>>1;

    while(pin > 0)
    {
        pin = pin >> 1;
        pinpos = pinpos + 1;
    }
    
    gpiox->MODER_R  &= ~( ((uint32_t)0x03) << (pinpos * 2));
    gpiox->MODER_R |= (((uint32_t)gpioinit->GPIO_Mode) << (pinpos * 2));

    //reg_pointer = (uint32_t *)PORTB_MODER_REGISTER;
    //debugprintRegister( *reg_pointer);

    gpiox->OSPEEDR_R  &= ~( ((uint32_t)0x03) << (pinpos * 2));
    gpiox->OSPEEDR_R|= (((uint32_t)gpioinit->GPIO_Speed) << (pinpos * 2));

    gpiox->OTYPER_R  &= ~( ((uint32_t)0x01) << (pinpos));
    gpiox->OTYPER_R |= (((uint32_t)gpioinit->GPIO_OType) << (pinpos));

    gpiox->PUPDR_R  &= ~( ((uint32_t)0x03) << (pinpos * 2));
    gpiox->PUPDR_R |= (((uint32_t)gpioinit->GPIO_PuPd) << (pinpos * 2));    
}

void GPIOPinAFConfig( GPIOTypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;
  
  
  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  GPIOx->AFR_R[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
  temp_2 = GPIOx->AFR_R[GPIO_PinSource >> 0x03] | temp;
  GPIOx->AFR_R[GPIO_PinSource >> 0x03] = temp_2;
}


void GPIOSetBits(GPIOTypeDef * gpiox, uint16_t gpiopin)
{
    gpiox->BSRRL_R = gpiopin;
}

void GPIOClearBits(GPIOTypeDef * gpiox, uint16_t gpiopin)
{
    gpiox->BSRRH_R = gpiopin;
}

void GPIOWrite(GPIOTypeDef * gpiox, uint16_t portval)
{
    gpiox->ODR_R = portval;
}

void GPIOToggleBits(GPIOTypeDef * gpiox, uint16_t gpiopin)
{
    gpiox->ODR_R = gpiox->ODR_R ^ gpiopin;
}

uint8_t GPIOReadInputDataBit( GPIOTypeDef * gpiox, uint16_t gpiopin)
{
    uint8_t bitstatus = 0;
    if ((gpiox->IDR_R & gpiopin) != (uint32_t)0)
    {
        bitstatus = 1;
    }
  return bitstatus;
}

uint16_t GPIOReadInputData( GPIOTypeDef * gpiox)
{
     return ((uint16_t)gpiox->IDR_R);
}