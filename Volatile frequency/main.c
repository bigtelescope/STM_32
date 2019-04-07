
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"

void SetDigit(int digit);

//#define FLASH_0LAT_DELAY0LAT
//#define FLASH_0LAT_DELAY1LAT
//#define FLASH_1LAT_DELAY0LAT
//#define FLASH_1LAT_DELAY1LAT

/**
  * System Clock Configuration
  * The system Clock is configured as follow :
  *    System Clock source            = PLL (HSI/2)
  *    SYSCLK(Hz)                     = 48000000
  *    HCLK(Hz)                       = 48000000
  *    AHB Prescaler                  = 1
  *    APB1 Prescaler                 = 1
  *    HSI Frequency(Hz)              = 8000000
  *    PLLMUL                         = 12
  *    Flash Latency(WS)              = 1
  */
static void rcc_config()
{
    /* Set FLASH latency */
#if defined(FLASH_0LAT_DELAY0LAT) || defined(FLASH_0LAT_DELAY1LAT)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
#else
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
#endif

    /* Enable HSI and wait for activation*/
    LL_RCC_HSI_Enable();
    while (LL_RCC_HSI_IsReady() != 1);

    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2,
                                LL_RCC_PLL_MUL_12);

    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1);

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

    /* Set APB1 prescaler */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    /* Update CMSIS variable (which can be updated also
     * through SystemCoreClockUpdate function) */
    SystemCoreClock = 48000000;
}

static void gpio_config(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
    return;
}

__attribute__((naked)) static void delay_5ms()
{
    asm ("push {r7, lr}");
    asm ("ldr r6, [pc, #8]");
    asm ("sub r6, #1");
    asm ("cmp r6, #0");
    asm ("bne delay_5ms+0x4");
    asm ("pop {r7, pc}");
    asm (".word 0x4000");
}

void CheckButton(int* number, int* button_state, int* flag)
{
  if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
      {
        *button_state = 1;
        *flag = 0;
      }   

      if(*button_state)
      {
        (*flag)++;
        delay_5ms();
      }
      if(*flag >= 7) 
      {
        (*number)++;
        
        *button_state = 0;
        *flag = 0;
      }
}

void PrintNumber(int counter, int number)
{
  switch(counter)
      {
        case 0:
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_4);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
          SetDigit(number % 10);
          break;

        case 1:
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
          SetDigit((number % 100)/10);
          break;

        case 2:
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
          SetDigit((number % 1000)/100);
          break;

        case 3:
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_4);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
          SetDigit((number % 10000)/1000);
          break;
      }
}

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

int main(void)
{
    rcc_config();
    gpio_config();

    int flag = 0;           //for bounce protection
    int temp = 0;           //for bounce protection
    int button_state = 0;   //for bounce protection
    int number = 1288;      //number on screen
    static int counter = 0; //counter for dinamic blinking

    while(1)
    {
      CheckButton(&number, &button_state, &flag);
      PrintNumber(counter, number);

      counter = (counter + 1) % 4;
      delay_5ms();
    }

    return 0;
}

