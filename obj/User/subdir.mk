################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/ch32v20x_pwm.c \
../User/main.c \
../User/system_ch32v20x.c 

OBJS += \
./User/ch32v20x_it.o \
./User/ch32v20x_pwm.o \
./User/main.o \
./User/system_ch32v20x.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/ch32v20x_pwm.d \
./User/main.d \
./User/system_ch32v20x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\suiki\�_�E�����[�h\CH32V20xEVT\EVT\EXAM\SRC\Debug" -I"D:\suiki\�_�E�����[�h\CH32V20xEVT\EVT\EXAM\SRC\Core" -I"D:\suiki\�_�E�����[�h\CH32V20xEVT\EVT\EXAM\TIM\PWM_All_Channel\User" -I"D:\suiki\�_�E�����[�h\CH32V20xEVT\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

