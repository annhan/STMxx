#include "stm32f1xx_hal.h"

#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC


static void MX_GPIO_Init(void);
void MX_GPIO_Deinit(void);
void SystemClock_Config(void);
void Error_Handler(void);

/*! \brief Jumps to the main application.
 */
#define APP_ADDRESS           0x08002000U
#define APPLICATION_START_ADDRESS   0x08004000U
typedef void (*pFunction)(void);
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void);
void Bootloader_JumpToApplication(void)
{
    uint32_t  JumpAddress = *(__IO uint32_t*)(APP_ADDRESS + 4);
    pFunction Jump = (pFunction)JumpAddress;
    
    HAL_RCC_DeInit();
    HAL_DeInit();
    
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;
    
#if (SET_VECTOR_TABLE)
    SCB->VTOR = APP_ADDRESS;
#endif
    
    __set_MSP(*(__IO uint32_t*)APP_ADDRESS);
    Jump();
}
char tam[1024] = "dsdsd";
int main(void) {
    HAL_Init();
    SystemClock_Config();

     MX_GPIO_Init();
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
    HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
      HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
      HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
     HAL_Delay(100);
     tam[0]='s';
     Bootloader_JumpToApplication();

        /*
          asm( "ldr   r1, =(0x08002000 + 4)\n\t"
               "ldr   r0, [r1]\n\t"
               "bx    r0" );
      */

      return 0;
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}
void MX_GPIO_Deinit(void)
{

    HAL_GPIO_DeInit(LED_GPIO_Port,LED_Pin);
      /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_DISABLE();
  __HAL_RCC_GPIOA_CLK_DISABLE();
}
void Error_Handler(void){}
void SysTick_Handler(void)
{
  HAL_IncTick();
}