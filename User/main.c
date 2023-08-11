#include "debug.h"

u16 control = 0, channel_control = 0, conpare_capture_enable = 0;

typedef enum {
  CH1,
  CH2,
  CH3,
  CH4,
} TimChannel;

typedef struct {
  u16 pin;
  GPIO_TypeDef *GPIOx;
  TIM_TypeDef *TIMx;
  TimChannel CHx;
} PinMap;

const PinMap PinMap_TIM[] = {
  { GPIO_Pin_0, GPIOA, TIM2, CH1 },   // TIM2_CH1
  { GPIO_Pin_1, GPIOA, TIM2, CH2 },   // TIM2_CH2
  { GPIO_Pin_2, GPIOA, TIM2, CH3 },   // TIM2_CH3
  { GPIO_Pin_3, GPIOA, TIM2, CH4 },   // TIM2_CH4
  { GPIO_Pin_6, GPIOA, TIM3, CH1 },   // TIM3_CH1
  { GPIO_Pin_7, GPIOA, TIM3, CH2 },   // TIM3_CH2
  { GPIO_Pin_8, GPIOA, TIM1, CH1 },   // TIM1_CH1
  { GPIO_Pin_9, GPIOA, TIM1, CH2 },   // TIM1_CH2
  { GPIO_Pin_10, GPIOA, TIM1, CH3 },  // TIM1_CH3
  { GPIO_Pin_11, GPIOA, TIM1, CH4 },  // TIM1_CH4
  { GPIO_Pin_0, GPIOB, TIM3, CH3 },   // TIM3_CH3
  { GPIO_Pin_1, GPIOB, TIM3, CH4 },   // TIM3_CH4
  { GPIO_Pin_6, GPIOB, TIM4, CH1 },   // TIM4_CH1
  { GPIO_Pin_7, GPIOB, TIM4, CH2 },   // TIM4_CH2
  { GPIO_Pin_8, GPIOB, TIM4, CH3 },   // TIM4_CH3
  { GPIO_Pin_9, GPIOB, TIM4, CH4 },   // TIM4_CH4
};

void pwmInit(u16 Pin, u16 Period, u16 Prescaler) {
  PinMap Pin_TIM = PinMap_TIM[Pin];
  u16 GPIO_Pin_x = Pin_TIM.pin;
  GPIO_TypeDef *GPIOx = Pin_TIM.GPIOx;
  TIM_TypeDef *TIMx = Pin_TIM.TIMx;
  TimChannel CHx = Pin_TIM.CHx;
  GPIO_InitTypeDef GPIO_InitStructure = { 0 };
  TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

  if (GPIOx == GPIOA) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  } else if (GPIOx == GPIOB) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  } else if (GPIOx == GPIOC) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  } else if (GPIOx == GPIOD) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  } else {
    printf("error\n");
  }

  if (TIMx == TIM1) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  } else if (TIMx == TIM2) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  } else if (TIMx == TIM3) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  } else if (TIMx == TIM4) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  } else {
    printf("error\n");
  }

  // GPIO setting
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOx, &GPIO_InitStructure);

  // TIM_TimeBaseInit
  TIM_TimeBaseInitStructure.TIM_Period = Period;
  TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);

  // TIM_OCxInit
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  switch (CHx) {
    case CH1:
      TIM_OC1Init(TIMx, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case CH2:
      TIM_OC2Init(TIMx, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case CH3:
      TIM_OC3Init(TIMx, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case CH4:
      TIM_OC4Init(TIMx, &TIM_OCInitStructure);
      TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    default:
      break;
  }
  TIMx->SWEVGR |= TIM_UG;
  TIM_CtrlPWMOutputs(TIMx, ENABLE);
  TIM_ARRPreloadConfig(TIMx, ENABLE);
  TIM_Cmd(TIMx, ENABLE);
}

void pwmWrite(u16 Pin, u16 Pulse) {
  PinMap Pin_TIM = PinMap_TIM[Pin];
  TIM_TypeDef *TIMx = Pin_TIM.TIMx;
  TimChannel CHx = Pin_TIM.CHx;
  switch (CHx) {
    case CH1:
      TIMx->CH1CVR = Pulse;
      break;
    case CH2:
      TIMx->CH2CVR = Pulse;
      break;
    case CH3:
      TIMx->CH3CVR = Pulse;
      break;
    case CH4:
      TIMx->CH4CVR = Pulse;
      break;
    default:
      break;
  }
  TIMx->SWEVGR |= TIM_UG;
}

int main(void) {

  for (int i = 0; i < 16; i++) {
    pwmInit(i, 255, 400);
  }
  Delay_Init();
  Delay_Ms(1000);
  while (1) {
      for (int j = 0; j <= 255; j++) {
          for (int i = 0; i < 16; i++) {

                pwmWrite(i, j);
              }

          Delay_Ms(30);
        }
  }
}
