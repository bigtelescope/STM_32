void SysTick_Handler(void)
{
    // These actions with macros are for frequency reducing
    static int delay = 0;
    DELAY(delay);

    counter = (counter + 1) % 4;

    if(delay)
    {
        PrintNumber(counter, score);
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_9);
    }
}

void EXTI0_1_IRQHandler(void)
{
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);
    
    if(snake.direct != RIGHT && snake.direct != LEFT)
    {
        prev_moving = snake.direct;
        snake.direct = LEFT;

        snake.turn_point_x = snake.head_x;
        snake.turn_point_y = snake.head_y;
    }

    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_1);
}


void EXTI2_3_IRQHandler(void)
{    
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);
    
    if(snake.direct != UP && snake.direct != DOWN)
    {
        prev_moving = snake.direct;
        snake.direct = DOWN;

        snake.turn_point_x = snake.head_x;
        snake.turn_point_y = snake.head_y;
    }

    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_2);
}

void EXTI4_15_IRQHandler(void)
{
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);

    if(snake.direct != LEFT && snake.direct != RIGHT)
    {
        prev_moving = snake.direct;
        snake.direct = RIGHT;

        snake.turn_point_x = snake.head_x;
        snake.turn_point_y = snake.head_y;
    }

    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_4);
}

void TIM2_IRQHandler(void)
{
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_8);
    
    if(snake.direct != DOWN && snake.direct != UP)
    {
        prev_moving = snake.direct;
        snake.direct = UP;

        snake.turn_point_x = snake.head_x;
        snake.turn_point_y = snake.head_y;
    }

    LL_TIM_ClearFlag_CC1(TIM2);
}