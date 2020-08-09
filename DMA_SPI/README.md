T = (1/APB_TIM_CLK in MHz) * (PRESCALER_Value + 1) * (PERIOD_Value + 1)
suppose:
APB_TIM_CLK = 8MHz
PRESCALER_Value = 999
PERIOD_Value = 7999
the formula is:
T= (1/8*10^6) * (999+1) * (7999+1) = 1s


Cài đặt ngắt timer định kì 
-----

- Timer 1 chọn chế độ ngắt là Timer_Update Interrup
