################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_sdhc.c \
../drivers/fsl_smc.c \
../drivers/fsl_sysmpu.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_sdhc.o \
./drivers/fsl_smc.o \
./drivers/fsl_sysmpu.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_sdhc.d \
./drivers/fsl_smc.d \
./drivers/fsl_sysmpu.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -D_DEBUG=1 -DUSB_STACK_FREERTOS -DUSB_STACK_FREERTOS_HEAP_SIZE=32768 -DSD_ENABLED -DSDK_OS_FREE_RTOS -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DSERIAL_PORT_TYPE_UART=1 -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\board" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\source" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\source\khci" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\drivers" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\inc" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\host" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\freertos\freertos_kernel\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\device" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\utilities" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\uart" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\serial_manager" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\lists" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\source" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\osa" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\CMSIS" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\osa" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\class" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\class\msc" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


