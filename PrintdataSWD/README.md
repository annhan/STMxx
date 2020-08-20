
# ***Debug GBD***
***makefile***
-----
```
gdb: all
	arm-none-eabi-gdb $(FIRMWARE) -x openocd.gdbinit
```
ta chi can make gdp laf se vao gaio dien gdp debug


***Visual Stdio***
--------
Configuring VS Code
Open the Debug panel (CTRL + SHIFT + D) and select “Add Configuration > GDB” through the top left dropdown arrow. Create a GDB configuration in launch.json and add the following. Note: Change the paths in “target”, “gdbpath”, and “autorun” to the correct locations.
```
{
    "name": "GDB",
    "type": "gdb",
    "request": "launch",
    "cwd": "${workspaceRoot}",
    "target": "${workspaceRoot}/.pioenvs/nucleo_f303k8/firmware.elf",
    "gdbpath" : "C:/STM32Toolchain/gcc-arm/5.4 2016q3/bin/arm-none-eabi-gdb.exe",
    "autorun": [
        "target remote localhost:3333",
        "symbol-file ./.pioenvs/nucleo_f303k8/firmware.elf",
        "monitor reset"
        ]
}
```
https://www.justinmklam.com/posts/2017/10/vscode-debugger-setup/

**Run GBD SERVER***
-----------

- Makefile add: 
```
load:
    openocd -f board/stm32f4.cfg
```
tên board tùy thuộc vào loại mình dùng.
Để running openocd server tại port 3333

***OpenOCD GBD Client***
----------

## ***Putty client***
----------

- Hostname : localhosst
- Port : 4444
- Chọn Telnet
- Khi dùng telnet ta bỏ chữ monitor giống trông câu lệnh

***Dùng MINGW64 client***
--------
Type ```arm-none-eabi-gbd.exe``` -> ```target remote localhost:3333``` để mở openocd terminal.

- ```monitor reset init```

- ```monitor reset halt``` reset micro

- ```monitor resume```

- ```monitor reset``` reset

- ```monitor halt``` stop

- ```monitor resume```

- ```monitor mdw 0x20000000 4``` Read 4 works tại địa chỉ này, địa chỉ này ứng với tên biến nào ta xem trong file ```.map``` của thư mục build.

    Add breakpoint là để chương trình chạy đến diểm breakpoint sẽ dừng và ta debug thanh ghi tại các lệnh tiếp theo.

- ```quit```

- ```monitor dp 0x080000C0 4 hw``` set breakpoint tại địa chỉ với chiều dài works 

Phieen ban ```monitor wp``` hoac ```rwp```

- ```monitor resume```

- ```monitor reset```

- ```monitor rdp 0x0800000C0  ``` remove breakpoint

# ***Debug Printf***

***Khai báo clock trong Cube***
----------------


***Khai báo chương trình***
-------------------
```c
/* USER CODE BEGIN Includes */
#include<stdio.h>
/* USER CODE END Includes */
```

```c
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};
/* USER CODE END PFP */
```
```c
* USER CODE BEGIN 4 */
/*send text over SWV*/
int fputc(int ch, FILE *f) {
    ITM_SendChar(ch);//send method for SWV
    return(ch);
}
/* USER CODE END 4 */
```

Hoac trong ham ```__write```

```c
int _write(int32_t file, uint8_t *ptr, int32_t len)
{
  /* Implement your write code here, this is used by puts and printf for example */
  int i=0;
  for(i=0 ; i<len ; i++)
  ITM_SendChar((*ptr++));
  return len;
}
```

```c
     printf("test text \n");
```
***Khai báo phần mềm***
------------


1. KeilC
2. OpenOCD
3. STLink Utility.
