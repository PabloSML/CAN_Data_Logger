################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_dspi.c \
../drivers/fsl_edma.c \
../drivers/fsl_flexcan.c \
../drivers/fsl_ftm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_pit.c \
../drivers/fsl_rtc.c \
../drivers/fsl_sdhc.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_dspi.o \
./drivers/fsl_edma.o \
./drivers/fsl_flexcan.o \
./drivers/fsl_ftm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_pit.o \
./drivers/fsl_rtc.o \
./drivers/fsl_sdhc.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_dspi.d \
./drivers/fsl_edma.d \
./drivers/fsl_flexcan.d \
./drivers/fsl_ftm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_pit.d \
./drivers/fsl_rtc.d \
./drivers/fsl_sdhc.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\board" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\source" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\sdmmc\template\sdhc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\source\generated" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\freertos\freertos_kernel\include" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\component\osa" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\freertos\template\ARM_CM4F" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\sdmmc\inc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\drivers" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\drivers\freertos" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\utilities" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\component\serial_manager" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\component\uart" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\fatfs\source" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\fatfs\source\fsl_mmc_disk" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\fatfs\source\fsl_ram_disk" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\fatfs\source\fsl_sd_disk" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\fatfs\source\fsl_usb_disk" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\sdmmc\host" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\sdmmc\osa" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\include" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\device\class\msc" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\output\source\device\class" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\device\include" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\device\source" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\device\class" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\output\source\device" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\device\source\khci" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\host" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\usb\host\class" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\gpio_driver" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\component\lists" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\CMSIS" -I"C:\Users\Matias\Documents\MCUXpressoIDE_11.4.1_6260\workspace\CAN_Data_Logger_Project\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


