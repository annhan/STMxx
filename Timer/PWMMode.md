Cấu hình STM Cube

1. Khởi tạo Timer chạy.

```HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);``` Timer2 kênh 1.

2. Điều chỉnh duty cycle.

- Chỉnh trực tiếp TIM2->CCR1 = CH1_DC; //Timer 2 với kênh 1 là CCR1 và CH1_DC là giá trị dutty.
- Chỉnh qua hàm ```__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, dutty) ```

3. Chỉnh tần số.


Trong STM32F1 có 4 Timer. Trong đó, Timer1 có cùng tần số xung clock với hệ thống là 72Mhz. Các Timer lại là 2,3,4 có tần số bằng một nữa. Tức là 36Mhz.

Để chỉnh tần số ta phải xác định độ phân giải của xung PWM.

Counter Period là độ phân giải PWM
Prescaler = (72000000)/(Tần số PWM * độ phân giải)
72000000 là tần số cấp cho khối timer, ta có thể tùy chỉnh
```
  htim1.Prescaler = 1000;
  htim1.Period = 35963;
```


