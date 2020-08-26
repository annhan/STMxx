Hàm kiểm tra nếu UART RX error thì restart nhận DMA.
 ```c
 // Check for UART errors and restart receive DMA transfer if required
 if (huart_->RxState != HAL_UART_STATE_BUSY_RX) {
    HAL_UART_AbortReceive(huart_);
    HAL_UART_Receive_DMA(huart_, dma_rx_buffer, sizeof(dma_rx_buffer));

}
```