#include "ch32v20x.h"
#include "ch32v20x_pwm.h"
#include "ch32v20x_rcc.h"
#include "ch32v20x_tim.h"

void pwmInit(u8 Channel, u16 Period, u16 Prescaler) {
  TimerPin pwm_pin = pinmap_timer[Channel];
  u16 GPIO_Pin_x = pwm_pin.pin;
  GPIO_TypeDef *GPIOx = pwm_pin.GPIOx;
  TIM_TypeDef *TIMx = pwm_pin.TIMx;
  u16 CHx = pwm_pin.CHx;
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
    case TIM_Channel_1:
      TIM_OC1Init(TIMx, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case TIM_Channel_2:
      TIM_OC2Init(TIMx, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case TIM_Channel_3:
      TIM_OC3Init(TIMx, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Disable);
      break;
    case TIM_Channel_4:
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

void pwmWrite(u8 Pin, u16 Pulse) {
  TimerPin pwm_pin = pinmap_timer[Pin];
  TIM_TypeDef *TIMx = pwm_pin.TIMx;
  u16 CHx = pwm_pin.CHx;
  switch (CHx) {
    case TIM_Channel_1:
      TIMx->CH1CVR = Pulse;
      break;
    case TIM_Channel_2:
      TIMx->CH2CVR = Pulse;
      break;
    case TIM_Channel_3:
      TIMx->CH3CVR = Pulse;
      break;
    case TIM_Channel_4:
      TIMx->CH4CVR = Pulse;
      break;
    default:
      break;
  }
  TIMx->SWEVGR |= TIM_UG;
}

void motorInit(u8 Channel, u16 Period, u16 Prescaler) {
  TimerPin motor_pin[2];
  u16 GPIO_Pin_x[2];
  GPIO_TypeDef *GPIOx[2] = { GPIOA, GPIOB };
  u16 CHx;
  motor_pin[0] = pinmap_motor[Channel];
  motor_pin[1] = pinmap_motor[Channel + 3];

  GPIO_InitTypeDef GPIO_InitStructure = { 0 };
  TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure = { 0 };

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  for (int i = 0; i < 2; i++) {
    GPIO_Pin_x[i] = motor_pin[i].pin;
    CHx = motor_pin[i].CHx;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x[i];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx[i], &GPIO_InitStructure);
  }

  // TIM_TimeBaseInit
  TIM_TimeBaseInitStructure.TIM_Period = Period;
  TIM_TimeBaseInitStructure.TIM_Prescaler = Prescaler - 1;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

  // TIM1_OCx, TIM1_OCxNInit
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  // Break, DeadTime Setting
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStructure.TIM_DeadTime = 0xFF;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);


  switch (CHx) {
    case TIM_Channel_1:
      TIM_OC1Init(TIM1, &TIM_OCInitStructure);
      TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
      break;
    case TIM_Channel_2:
      TIM_OC2Init(TIM1, &TIM_OCInitStructure);
      TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable);
      break;
    case TIM_Channel_3:
      TIM_OC3Init(TIM1, &TIM_OCInitStructure);
      TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Disable);
      break;
    default:
      break;
  }
  TIM1->SWEVGR |= TIM_UG;
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_ARRPreloadConfig(TIM1, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

void motorWrite(u8 Pin, u16 Pulse) {
  TimerPin pwm_pin = pinmap_timer[Pin];
  u16 CHx = pwm_pin.CHx;
  switch (CHx) {
    case TIM_Channel_1:
      TIM1->CH1CVR = Pulse;
      break;
    case TIM_Channel_2:
      TIM1->CH2CVR = Pulse;
      break;
    case TIM_Channel_3:
      TIM1->CH3CVR = Pulse;
      break;
    default:
      break;
  }
  TIM1->SWEVGR |= TIM_UG;
}
