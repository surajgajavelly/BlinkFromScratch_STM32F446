#include <stdint.h>

// Registers for F446RE (Manual Definitions)
#define RCC_BASE           0x40023800UL
#define RCC_AHB1ENR        (*(volatile uint32_t *)(RCC_BASE + 0x30UL))

#define GPIOA_BASE         0x40020000UL
#define GPIOA_MODER        (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR          (*(volatile uint32_t *)(GPIOA_BASE + 0x14UL))

int main(void)
{
    // 1. Enable Clock for GPIOA (Bit 0)
    RCC_AHB1ENR |= (1 << 0); 

    // 2. Set PA5 to Output Mode (01 at bits 11:10)
    GPIOA_MODER &= ~(3 << 10); // Clear
    GPIOA_MODER |= (1 << 10);  // Set

    while(1)
    {
        // LED ON (PA5 High)
        GPIOA_ODR |= (1 << 5);
        
        for(volatile int i = 0; i < 1000000; i++); 

        // LED OFF (PA5 Low)
        GPIOA_ODR &= ~(1 << 5);

        for(volatile int i = 0; i < 1000000; i++);
    }
}