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
```
     printf("test text \n");
/* US
```
***Khai báo phần mềm***
------------


1. KeilC
2. OpenOCD
3. STLink Utility.

# ***Debug GBD***

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