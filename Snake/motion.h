void goRight()
{
    temp = snake.head_x - snake.turn_point_x;

    if(temp <= snake.lenght)
    {
        oled_set_pix(snake.head_x, snake.head_y, clWhite);

        if(prev_moving == UP)
            oled_set_pix(snake.turn_point_x, snake.turn_point_y - temp + snake.lenght + 1, clBlack);
        else
            oled_set_pix(snake.turn_point_x, snake.turn_point_y + temp - snake.lenght - 1, clBlack);

        snake.head_x++;
    }
    else
    {
        for(int i = 0; i < snake.lenght; i++)
        {
            oled_set_pix(snake.head_x - i, snake.head_y, clWhite);
            oled_set_pix(snake.head_x - 1 - snake.lenght, snake.head_y, clBlack);
        }

        snake.head_x++;
    }
}

void goLeft()
{
    temp = snake.turn_point_x - snake.head_x;

    if(temp <= snake.lenght)
    {
        oled_set_pix(snake.head_x, snake.head_y, clWhite);

        if(prev_moving == UP)
            oled_set_pix(snake.turn_point_x, snake.turn_point_y - temp + snake.lenght + 1, clBlack);
        else
            oled_set_pix(snake.turn_point_x, snake.turn_point_y + temp - snake.lenght - 1, clBlack);

        snake.head_x--;
    }
    else
    {
        for(int i = 0; i <= snake.lenght; i++)
        {
            oled_set_pix(snake.head_x + i, snake.head_y, clWhite);
            oled_set_pix(snake.head_x + 1 + i, snake.head_y, clBlack);
        }

        snake.head_x--;
    }
}

void goUp()
{
    temp = snake.turn_point_y - snake.head_y;

    if(temp <= snake.lenght)
    {
        oled_set_pix(snake.head_x, snake.head_y, clWhite);

        if(prev_moving == LEFT)
            oled_set_pix(snake.turn_point_x - temp + snake.lenght + 1, snake.turn_point_y, clBlack);
        else
            oled_set_pix(snake.turn_point_x  + temp - snake.lenght - 1, snake.turn_point_y, clBlack);

        snake.head_y--;
    }
    else
    {
        for(int i = 0; i <= snake.lenght; i++)
        {
            oled_set_pix(snake.head_x, snake.head_y + i, clWhite);
            oled_set_pix(snake.head_x, snake.head_y + snake.lenght + 1, clBlack);
        }

        snake.head_y--;
    }
}

void goDown()
{
    temp = snake.head_y - snake.turn_point_y;

    if(temp <= snake.lenght)
    {
        oled_set_pix(snake.head_x, snake.head_y, clWhite);

        if(prev_moving == LEFT)
            oled_set_pix(snake.turn_point_x - temp + snake.lenght + 1, snake.turn_point_y, clBlack);
        else
            oled_set_pix(snake.turn_point_x  + temp - snake.lenght - 1, snake.turn_point_y, clBlack);

        snake.head_y += 1;
    }
    else
    {
        for(int i = 0; i <= snake.lenght; i++)
        {
            oled_set_pix(snake.head_x, snake.head_y - i, clWhite);
            oled_set_pix(snake.head_x, snake.head_y - snake.lenght - 1, clBlack);
        }

        snake.head_y += 1;
    }
}

void SetFood()
{
    food_x = rand() % LENGHT + ZERO;
    food_y = rand() % HEIGHT + ZERO;

    oled_set_pix(food_x,            food_y,          clWhite);
    oled_set_pix(food_x,            food_y - INDENT, clWhite);
    oled_set_pix(food_x,            food_y + INDENT, clWhite);
    oled_set_pix(food_x - INDENT,   food_y,          clWhite);
    oled_set_pix(food_x + INDENT,   food_y,          clWhite);
}

void KillFood()
{
    score++;

    oled_set_pix(food_x,            food_y,          clBlack);
    oled_set_pix(food_x,            food_y - INDENT, clBlack);
    oled_set_pix(food_x,            food_y + INDENT, clBlack);
    oled_set_pix(food_x - INDENT,   food_y,          clBlack);
    oled_set_pix(food_x + INDENT,   food_y,          clBlack);

    SetFood();
}

void Endgame()
{
    xprintf(" \n\n\n\n oh no, you've losed!\n");
    xprintf("          :(");
    oled_update();

    while(1);
}

void Check()
{
    if(snake.head_x == ZERO || snake.head_x == LENGHT)
        Endgame();

    if(snake.head_y == ZERO || snake.head_y == HEIGHT)
        Endgame();


    if(abs(snake.head_x - food_x) <= INDENT &&
       abs(snake.head_y - food_y) <= INDENT)
       KillFood();
}