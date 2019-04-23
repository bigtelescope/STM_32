#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_tim.h"

void SetDigit(int digit);
void PrintNumber(int counter, double number);

void gpio_config(void);
void rcc_config();

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

static void timers_config(void)
{
    //Configure input channel
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_5, LL_GPIO_AF_2);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_5, LL_GPIO_PULL_UP);

    /*
     * Setup timer to capture input mode
     */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
    LL_TIM_SetPrescaler(TIM2, 47999);
    LL_TIM_IC_SetFilter(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV32_N8);
    LL_TIM_IC_SetPolarity(TIM2, LL_TIM_CHANNEL_CH1,
                          LL_TIM_IC_POLARITY_FALLING);

    LL_TIM_IC_SetActiveInput(TIM2, LL_TIM_CHANNEL_CH1,
                             LL_TIM_ACTIVEINPUT_DIRECTTI);

    LL_TIM_IC_SetPrescaler(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableIT_CC1(TIM2);
    LL_TIM_EnableCounter(TIM2);
    /*
     * Setup NVIC
     */
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_SetPriority(TIM2_IRQn, 1);

    LL_TIM_GenerateEvent_UPDATE(TIM2);
}

static int counter = 0; //counter for dinamic blinking
static double prev = 0;
static double next = 0;
static double time;

void TIM2_IRQHandler(void)
{
    prev = next;
    next = LL_TIM_IC_GetCaptureCH1(TIM2);
    if((next - prev) > 150)
    {
        time = (next - prev) / 1000;
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);
        LL_TIM_ClearFlag_CC1(TIM2);
    }
}

int main(void)
{
    rcc_config();
    gpio_config();
    timers_config();

    while (1)
    {
      PrintNumber(counter, time);

      counter = (counter + 1) % 4;
      delay_5ms();
    }
    return 0;
}
