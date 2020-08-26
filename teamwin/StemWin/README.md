# Cấu hình steamwin

STemWin Library là một bộ xếp thư viện graphic chuyên nghiệp cho phép xây dựng giao diện người dùng (GUIs) với bất kì MCU STM32 nào, bất kỳ LCD/TFT nào.


Tạo project bình thường.
Bật các ngoại vi DMA2D, LTDC, SDRAM, CRC

- Copy thu viện BSP tới drivers của chương trình

**LTDC (LCD -> TFT)**
-----
Các tín hiệu LCD-TFT
Tín hiệu LCD-TFT	Mô tả
LCD_CLK	Ngõ ra xung clock pixel
LCD_HSYNC	Đồng bộ hàng ngang
LCD_VSYNC	Đồng bộ hàng dọc
LCD_DE	Data enable
LCD_R[7:0]	8-bit dữ liệu màu Red
LCD_G[7:0]	8-bit dữ liệu màu Green
LCD_B[7:0]	8-bit dữ liệu màu Blue

***Flexible memory controller (FMC)***
-------------

 gồm có 3 bộ điều khiển:

Bộ điều khiển bộ nhớ NOR/PSRAM
Bộ điều khiển NAND/PC Card
Bộ điều khiển Synchronous DRAM

***Chrom-Art Accelerator (DMA2D)***
--------------

Chrom-Art Accelerator (DMA2D) là đặc trưng riêng của DMA thao tác ảnh. Nó có thể thực hiện:

Đổ đầy một bộ phận hay toàn bộ ảnh đích với màu sắc xác định.
Copy một phần hoặc toàn bộ ảnh nguồn tới một phần hoặc toàn bộ ảnh đích.
Copy một phần hoặc toàn bộ một ảnh đích tới một phần hoặc toàn bộ một ảnh đích với một bộ chuyển đổi định dạng pixel.

Blending một phần và/hoặc hai ảnh nguồn hoàn toàn với định dạng pixel khác nhau và copy kết quả vào một phần hoặc toàn bộ tới một ảnh đích với một định dạng màu sắc khác.

Mọi sự phối hợp màu kinh điển được hỗ trờ từ 4-bit lên tới 32-bit trên pixel với chế độ màu sắc tra bảng hoặc trược tiếp. DMA2D có bộ nhớ chuyên cho CLUTs (bảng tra cứu màu).

# **Dùng   HAL_SYSTICK_Callback()**

Khi không dùng RTOS thì phải dùng hàm systick để  tăng biến ```OS_TimeMS```
```c
extern volatile GUI_TIMER_TIME OS_TimeMS;
void HAL_SYSTICK_Callback(void)
{
		OS_TimeMS++;
}
```

- Khai báo trong file stm32f7xx_it.c để sử dụng systick

```c
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
  /* USER CODE END SysTick_IRQn 0 */
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}
``` 
 

    HAL_SYSTICK_IRQHandler();