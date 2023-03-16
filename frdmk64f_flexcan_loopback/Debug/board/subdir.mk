################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFLEXCAN_WAIT_TIMEOUT=1000 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\board" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\source" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\utilities" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\drivers" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\device" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\component\uart" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\component\lists" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\CMSIS" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_flexcan_loopback\frdmk64f\driver_examples\flexcan\loopback" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


