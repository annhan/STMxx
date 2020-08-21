# **Debug SWO hay GBD trực tiếp trên visual stdio**

- Cài plugin hỗ trợ là ```cotex-debug```
- tạo thư mục lập trình và chỉnh sữa file ```launch.json```
- tải về file svd.

```c

        {
            "name": "(Windows) Launch",
            "type": "cortex-debug",                    // type
            "request": "launch",
            "cwd": "${workspaceFolder}",    
            "servertype": "openocd",                 // giao diện openocd
            "executable": "./build/USB_CDC.elf",     // file elf chạy
            "device": "STM32F746",
            "configFiles": [
                "interface/stlink-v2-1.cfg",  //interface của openocd
                "target/stm32f7x.cfg"
            ],
            "svdFile": "${workspaceRoot}/.vscode/STM32F7x6.svd",
            "swoConfig": {
                "enabled": true,
                "cpuFrequency": 200000000,  //tần số CPU
                "swoFrequency": 2000000,    // tần số swo
                "source": "probe",
                "decoders": [
                    { "type": "console", "label": "ITM", "port": 0 } // Hiên thị ở bảng debug
                ]
            }
        }
    ]
}
```

![hinh](doc/debug.PNG)

** Fix loi**
----------


File viet laf ```usb_cdc_if.c```
```c
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

//Du lieu truyen va nhan se duoc liuu vao bien nay
/* Received Data over USB are stored in this buffer       */

uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/* Send Data over USB CDC are stored in this buffer       */

uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

```

hamf callback nhan data
```c
static int8_t CDC_Receive_FS (uint8_t* Buf, uint32_t *Len){
    /**
     * Nhan data
     * /
     USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]); //Xoa du lieu sau khi nhan
     USBD_CDC_ReceivePacket(&hUsbDeviceFS);
     return (USBD_OK);
}
```
Ham truyen data
```c
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
```