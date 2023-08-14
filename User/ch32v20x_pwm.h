#include "ch32v20x.h"

typedef struct {
  GPIO_TypeDef *GPIOx;
  u16 pin;
  TIM_TypeDef *TIMx;
  u16 CHx;
} TimerPin;

const TimerPin pinmap_timer[] = {
  { GPIOA, GPIO_Pin_8, TIM1, TIM_Channel_1 },   // TIM1_CH1
  { GPIOA, GPIO_Pin_9, TIM1, TIM_Channel_2 },   // TIM1_CH2
  { GPIOA, GPIO_Pin_10, TIM1, TIM_Channel_3 },   // TIM1_CH3
  { GPIOA, GPIO_Pin_11, TIM1, TIM_Channel_4 },   // TIM1_CH4
  { GPIOA, GPIO_Pin_0, TIM2, TIM_Channel_1 },   // TIM2_CH1
  { GPIOA, GPIO_Pin_1, TIM2, TIM_Channel_2 },   // TIM2_CH2
  { GPIOA, GPIO_Pin_2, TIM2, TIM_Channel_3 },   // TIM2_CH3
  { GPIOA, GPIO_Pin_3, TIM2, TIM_Channel_4 },   // TIM2_CH4
  { GPIOA, GPIO_Pin_6, TIM3, TIM_Channel_1 },   // TIM3_CH1
  { GPIOA, GPIO_Pin_7, TIM3, TIM_Channel_2 },   // TIM3_CH2
  { GPIOB, GPIO_Pin_0, TIM3, TIM_Channel_3 },  // TIM3_CH3
  { GPIOB, GPIO_Pin_1, TIM3, TIM_Channel_4 },  // TIM3_CH4
  { GPIOB, GPIO_Pin_6, TIM4, TIM_Channel_1 },  // TIM4_CH1
  { GPIOB, GPIO_Pin_7, TIM4, TIM_Channel_2 },  // TIM4_CH2
  { GPIOB, GPIO_Pin_8, TIM4, TIM_Channel_3 },  // TIM4_CH3
  { GPIOB, GPIO_Pin_9, TIM4, TIM_Channel_4 },  // TIM4_CH4
};

const TimerPin pinmap_motor[] = {
  { GPIOA, GPIO_Pin_8, TIM1, TIM_Channel_1 },   // TIM1_CH1
  { GPIOA, GPIO_Pin_9, TIM1, TIM_Channel_2 },   // TIM1_CH2
  { GPIOA, GPIO_Pin_10, TIM1, TIM_Channel_3 },   // TIM1_CH3
  { GPIOB, GPIO_Pin_12, TIM1, TIM_Channel_1 },  // TIM1_CH1N
  { GPIOB, GPIO_Pin_13, TIM1, TIM_Channel_2 },  // TIM1_CH2N
  { GPIOB, GPIO_Pin_14, TIM1, TIM_Channel_3 },  // TIM1_CH3N
};

void pwmInit(u8 Pin, u16 Period, u16 Prescaler);
void pwmWrite(u8 Pin, u16 Pulse);

void motorInit(u8 Channel, u16 Period, u16 Prescaler);
void motorWrite(u8 Channel, u16 Pulse);
