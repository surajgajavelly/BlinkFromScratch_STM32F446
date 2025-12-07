#include <stdint.h>

#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128U * 1024U) 
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata; 
    uint8_t *pSrc = (uint8_t*)&_etext; 
    
    for(uint32_t i = 0; i < size; i++) 
    {
        *pDst++ = *pSrc++;
    }

    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;
    
    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;  // Initialize .bss section to zero
    } 

    main();
}

void Default_Handler(void)
{
    while(1);
}

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler,
    0, 0, 0, 0,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler,
    0,
    (uint32_t)Default_Handler,
    (uint32_t)Default_Handler
};