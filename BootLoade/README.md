- Tạo chương trình bootloader trước khi chạy ứng dụng chính
- STM sẽ begin code tại địa chỉ 0x8000000, ta sẽ viết boodleader tại đây và main code sẽ dời lại 1 địa chỉ khác phía sau.

Chúng ta cần chỉnh sữa file ld cho ứng dụng bootloader và cho mainapp.

***File ld của bootloader.***
--------

1. File LD

```
MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 64K
}
```
 Bộ nhớ Flash của STM32f103C8 là 64Kb, nếu ta giới hạn bộ nhớ bootloader là 4kb thì ta sẽ sữa
 ```
 MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 4K //bắt đầu ở 0x8000000 vỡi chiều dài 2K
}
 ```

 ***File của MainApp.***
 ----------------

 ***1. File ld.***

```
MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 64K
}
```
 ta sữa lại
```
PROVIDE(__image_addr = 0x08010000); //khai bao biến chưa địa chỉ begin maincode để gọi trong hàm main.c của bootloader
MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
FLASH (rx)      : ORIGIN = 0x8001000, LENGTH = (64-4)K 
//chiều dài ngắn đi 4K do dùng cho bootloader.
//Địa chỉ bằng 0x80000000 + 4Kb=4*1024=4096 (DEC) = 1000 (HEX) ->ORIGIN = 0x8001000
}
```

***2. File system_stm32fAxx.c***

Ta cần remap interrupt vector table đến vị trí đầu của chương trình ứng dụng:
IMAGE_ADDR = 0x08000000  + BOOTLOADER_MAX_SIZE = 0x8001000

```/* Do remap interrupt vector */ SCB->VTOR = IMAGE_ADDR;  ``` Hoặc ```/* Do remap interrupt vector */ SCB->VTOR = 0x08001000;  ```

***Code Jump tới mainCode***
---------------

```c
#define APP_ADDRESS           0x08002000U
typedef void (*pFunction)(void);
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void);
void Bootloader_JumpToApplication(void)
{
    uint32_t  JumpAddress = *(__IO uint32_t*)(APP_ADDRESS + 4);
    pFunction Jump = (pFunction)JumpAddress;
    
    HAL_RCC_DeInit();
    HAL_DeInit();
    
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;
    
#if (SET_VECTOR_TABLE)
    SCB->VTOR = APP_ADDRESS;
#endif
    
    __set_MSP(*(__IO uint32_t*)APP_ADDRESS);
    Jump();
}
```
Maincode __image_addr không phải là entry point(```Reset_Handler```) của ứng dụng, nó thật sự là giá trị con trỏ stack pointer (SP). 

Giá trị ô nhớ tại vị trí (__image_addr + 4) mới đúng là vị trí của hàm ```Reset_Handler```

***Sữa make file***
------

Chỉ khai báo những cái cần:

 Sữa LDSCRIPT = bootloader/STM32F103C8Tx_FLASH.ld
 
 BUILD_DIR = bootloader/build
 
 C_SOURCES =  \
bootloader/src/main.c \
bootloader/src/system_stm32f1xx.c

***OpenOCD***
--------------
```
flash_all: #write 2 flash bootloader va mainapp
	$(OPENOCD)	-c "init" \
	-c "program $(FIRMWARE) 0x8002000 verify" \
	-c "program $(BOOTLOADER) 0x08000000 verify" \ //ghi file bin với địa chỉ cụ thể
	-c "exit"
 ```
 Ghi bộ nhớ vào địa chỉ cụ thể
