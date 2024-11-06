################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/gpio.c \
../Src/huffman.c \
../Src/interrupt.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/text_comp_decomp.c \
../Src/timer.c \
../Src/usart.c \
../Src/util.c 

OBJS += \
./Src/gpio.o \
./Src/huffman.o \
./Src/interrupt.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/text_comp_decomp.o \
./Src/timer.o \
./Src/usart.o \
./Src/util.o 

C_DEPS += \
./Src/gpio.d \
./Src/huffman.d \
./Src/interrupt.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/text_comp_decomp.d \
./Src/timer.d \
./Src/usart.d \
./Src/util.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"D:/Users/user/Downloads/STM32F4_Arbre_huffman-main-20241106T121648Z-001/STM32F4_Arbre_huffman-main/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Users/user/Downloads/STM32F4_Arbre_huffman-main-20241106T121648Z-001/STM32F4_Arbre_huffman-main/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/huffman.cyclo ./Src/huffman.d ./Src/huffman.o ./Src/huffman.su ./Src/interrupt.cyclo ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/text_comp_decomp.cyclo ./Src/text_comp_decomp.d ./Src/text_comp_decomp.o ./Src/text_comp_decomp.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su ./Src/usart.cyclo ./Src/usart.d ./Src/usart.o ./Src/usart.su ./Src/util.cyclo ./Src/util.d ./Src/util.o ./Src/util.su

.PHONY: clean-Src

