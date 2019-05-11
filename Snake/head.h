#ifndef HEAD_H
#define HEAD_H

#include <stdlib.h>
#include <math.h>

#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_tim.h"
#include "xprintf.h"
#include "oled_driver.h"

#define LENGHT 			128 // Screen lenght
#define HEIGHT 			64  // Screen height
#define START_X 		64  // Initial coordinate
#define START_Y 		32  // Initial coordinate
#define START_LENGHT 		5   // Initial lenght
#define RIGHT 			1	
#define LEFT 			2
#define UP 			3
#define DOWN			4
#define INDENT 			2   // Constant for fruit creating
#define ZERO 			0

#define CHECK_DELAY 	150 // Constant for contacts bounce problem solving

#define CONVERT_TO_SEC	(ARG) (ARG) = (ARG) / 1000
#define DELAY(ARG) 		(ARG) = ((ARG) + 1) % 5;

struct Snake
{
	char 	head_x;
	char 	head_y;
	char 	lenght;
	char 	direct;
	char 	turn_point_x;			// Coordinate of snake body turn
	char	turn_point_y;			// Coordinate of snake body turn
};


static struct Snake snake;			// Game object

static char		counter;		// A counter for dinamic blinking
static int 		score;			// Total score

static char 		food_x;			// First food coordinate
static char 		food_y;			// Second food coordinate

static char 		prev_moving;		// For snake curve realixation

static char 		temp;			// Temporary variable for different calculations

void SetDigit		(int digit);			// Sets digit :)
void PrintNumber	(int counter, double number);	// Realization of dynamic	indication
void SetFood		();				// Sets a fruit on a screen
void KillFood		();				// Kill a fruit and calls SetFood()
void Check 		();				// Checking for total score and endgame
void Endgame		();				// Stops game

void goRight		();
void goLeft		();
void goUp		();
void goDown		();

void gpio_config	();
void rcc_config		();
void exti_config	();
void timers_config	();
void printf_config	();
void systick_config	();
void printf_config	();

void SysTick_Handler	 ();				// LED indication each 0.001 seconds
void EXTI0_1_IRQHandler	 ();				// A1 Handler
void TIM2_IRQHandler	 ();				// A5 Handler
void EXTI4_15_IRQHandler ();				// A4 Handler
void EXTI2_3_IRQHandler	 ();				// A2 Han


#endif
