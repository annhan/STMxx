***Flash-based Non-Volatile Memory (NVM)***
------------

Tìm tài liệu flash memory address của IC và xác định vùng flash ta sẽ ghi dữ liệu.

So the STM32F103C8T6 bộ nhớ flash bắt đầu từ 0x08000000 và có chiều dài 64Kb.

Ta chia ra cho phân vùng bootloader là 8Kb và mainapp sẽ còn 56Kb

***Code***
-------------

- FreeRTOS với mutex and threading.



134217728 to end page 1 là (134217728 + 1023) - 1 = 134218751 -> 0x0800 03FF
(134217728 + (64*1024)) - 1 = 0x0800FFFF

Mỗi Page có 1Kb Flash, khi lập trình ta nên chọn theo từng page vì việc xóa Flash sẽ xóa theo page.
