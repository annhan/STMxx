***Cài đặt ngắt timer định kì***
---------

Timer 1 chọn chế độ ngắt là Timer_Update Interrup.

Cách tính thời gian T **T = (1/APB_TIM_CLK in MHz) * (PRESCALER_Value + 1) * (PERIOD_Value + 1)**
```
APB_TIM_CLK = 72Mhz
PRESCALER_Value = 1000
PERIOD_Value = 7200
->T=(1001 * 7201)/72000000=0.1s
```
```
Tính T = 0.5s
(1001 * A ) = 72000000 * 0.5 = 36000000
->A = 35964 ->PERIOD_Value = 35963
```

***Code***
--------
Xem phần [DMA_SPI](DMA_SPI) phần này sẽ định thời timer ngắt trong vòng 0.5s để gửi SPI.
