#include "stm32f0xx_hal.h"

// Function prototypes
static void MX_GPIO_Init(void);
void SystemClock_Config(void);

int main(void) {
    // Reset all peripherals, initialize the Flash interface and the Systick
    HAL_Init();
    
    // Configure the system clock
    SystemClock_Config();
    
    // Initialize the GPIO pins
    MX_GPIO_Init();

    // The infinite loop
    while (1) {
        // Read the Light Barrier on PC0
        // (If the sensor logic is inverted, change GPIO_PIN_SET to GPIO_PIN_RESET)
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_SET) {
            
            // Beam interrupted: Turn the buzzer ON (PF4)
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET); 
            
        } else {
            // Beam clear: Turn the buzzer OFF (PF4)
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET); 
        }
    }
}

// GPIO Initialization Function
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // CRITICAL UPDATE: Enable the clocks for GPIO Port C and Port F
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // 1. Configure PC0 as Input (KY-010 Light Barrier)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL; // The module already has a pull-up resistor
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // 2. Configure PF4 as Output (KY-012 Buzzer via 220-ohm resistor)
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull output
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

// Minimal System Clock Configuration for default internal 8MHz HSI
void SystemClock_Config(void) {
    // Left empty: relies on default 8MHz clock which is plenty for simple GPIO
}

// Required for the HAL library time base
void SysTick_Handler(void) {
    HAL_IncTick();
}