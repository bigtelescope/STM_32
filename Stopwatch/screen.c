#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_bus.h"

void SetDigit(int digit);
void PrintNumber(int counter, double number);

// Realizes dinamic indication and shows you number 
// from an argument list
void PrintNumber(int counter, double number)
{
  int coma = 0;
  int mult = 0;

  if(number < 10)
  {
    coma = 3;
    mult = 1000;
  }
  else if(number < 100)
  {
    coma = 2;
    mult = 100;
  }
  else if(number < 1000)
  {
    mult = 10;
    coma = 1;
  }

  switch(counter)
  {
    case 0:
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
      SetDigit(((int)(number * mult)) % 10);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);

      break;

    case 1:
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
      SetDigit(((int)(number * mult) % 100)/10);
      if(coma == 1)
        LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0);
      else
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);

      break;

    case 2:
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
      SetDigit(((int)(number * mult) % 1000)/100);
      if(coma == 2)
        LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0);
      else
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);

      break;

    case 3:
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
      SetDigit(((int)(number * mult) % 10000)/1000);
      if(coma == 3)
        LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0);
      else
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
      
      break;

    default :
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_5);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_6);
      LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7);
      break;
  }
}

//Creates a digit on a LED segment
void SetDigit(int digit)
{
  switch(digit)
  {
    case 0:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 1:
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 2:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 3:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 4:
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 5:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 6:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 7:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 8:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;

    case 9:
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_6);
      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7);
      break;
  }
}