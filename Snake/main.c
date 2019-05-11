#include "head.h"
#include "control.h"
#include "motion.h"
#include "screen.h"
#include "system.h"

int main(void)
{
    rcc_config();
    gpio_config();
    timers_config();
    systick_config();
    exti_config();
    oled_config();
    printf_config();

    // primary initialization
    snake.head_x = START_X;
    snake.head_y = START_Y;
    snake.lenght = START_LENGHT;
    snake.direct = RIGHT;

    temp = 0;
    score = 0;

    SetFood();

    while (1)
    {
       Check();

        switch(snake.direct)
        {
            case RIGHT:
                goRight();
                break;

            case LEFT:
                goLeft();
                break;

            case UP:
                goUp();
                break;

            case DOWN:
                goDown();
                break;
        }

        oled_update();
    }
    return 0;
}
