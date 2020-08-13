***Dời Mainapp***
--------

- Dời Địa chỉ Flash khởi động chương trình lên 32K từ 0x0800000 lên 0x08008000
- Chừa 32K flash để lưu data

```
MEMORY
{
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 320K
FLASH (rx)      : ORIGIN = 0x8008000, LENGTH = 992K  //1024-32 còn 992K
}
```


Thay đổi ```#define VECT_TAB_OFFSET  0x00``` trong file system_stm32f7xx.c thành ```#define VECT_TAB_OFFSET  0x8000 ```
***Để thay đổi địa chỉ khởi động mà không viết bootloader ta có thể dùng  STM32 ST-Link Utility. 2. Menu -> Target -> Option Bytes***

