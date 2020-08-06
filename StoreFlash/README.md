Flash-based Non-Volatile Memory (NVM)
Tìm tài liệu flash memory address của IC và xác định vùng flash ta sẽ ghi dữ liệu.
So the STM32F103C8T6 is STM32F103 plus:
C = 48 pins
8 = 64 Kbytes flash
Từ 0x0800 0000 to 
134217728 to end page 1 là (134217728 + 1023) - 1 = 134218751 -> 0x0800 03FF
(134217728 + (64*1024)) - 1 = 0x0800FFFF

Mỗi Page có 1Kb Flash, khi lập trình ta nên chọn theo từng page vì việc xóa Flash sẽ xóa theo page.