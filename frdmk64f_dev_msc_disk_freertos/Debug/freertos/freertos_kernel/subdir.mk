################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/croutine.c \
../freertos/freertos_kernel/event_groups.c \
../freertos/freertos_kernel/list.c \
../freertos/freertos_kernel/queue.c \
../freertos/freertos_kernel/stream_buffer.c \
../freertos/freertos_kernel/tasks.c \
../freertos/freertos_kernel/timers.c 

OBJS += \
./freertos/freertos_kernel/croutine.o \
./freertos/freertos_kernel/event_groups.o \
./freertos/freertos_kernel/list.o \
./freertos/freertos_kernel/queue.o \
./freertos/freertos_kernel/stream_buffer.o \
./freertos/freertos_kernel/tasks.o \
./freertos/freertos_kernel/timers.o 

C_DEPS += \
./freertos/freertos_kernel/croutine.d \
./freertos/freertos_kernel/event_groups.d \
./freertos/freertos_kernel/list.d \
./freertos/freertos_kernel/queue.d \
./freertos/freertos_kernel/stream_buffer.d \
./freertos/freertos_kernel/tasks.d \
./freertos/freertos_kernel/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/%.o: ../freertos/freertos_kernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -D_DEBUG=1 -DUSB_STACK_FREERTOS -DUSB_STACK_FREERTOS_HEAP_SIZE=32768 -DSD_ENABLED -DSDK_OS_FREE_RTOS -DFSL_OSA_BM_TASK_ENABLE=0 -DFSL_OSA_BM_TIMER_CONFIG=0 -DSERIAL_PORT_TYPE_UART=1 -DMCUXPRESSO_SDK -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=0 -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\board" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\source" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\source\khci" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\drivers" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\inc" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\host" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\freertos\freertos_kernel\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\device" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\utilities" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\uart" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\serial_manager" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\lists" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\include" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\source" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\component\osa" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\CMSIS" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\sdmmc\osa" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\class" -I"F:\Pablo\Documents\MCUXpressoIDE_11.4.1_6260\workspace\frdmk64f_dev_msc_disk_freertos\usb\device\class\msc" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


