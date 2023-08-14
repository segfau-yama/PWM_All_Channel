################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/suiki/ダウンロード/CH32V20xEVT/EVT/EXAM/SRC/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: D:/suiki/ダウンロード/CH32V20xEVT/EVT/EXAM/SRC/Debug/debug.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\suiki\ダウンロード\CH32V20xEVT\EVT\EXAM\SRC\Debug" -I"D:\suiki\ダウンロード\CH32V20xEVT\EVT\EXAM\SRC\Core" -I"D:\suiki\ダウンロード\CH32V20xEVT\EVT\EXAM\TIM\PWM_All_Channel\User" -I"D:\suiki\ダウンロード\CH32V20xEVT\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

