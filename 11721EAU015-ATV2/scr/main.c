#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define STM32_RCC_BASE  0x40023800      // Reset and clock control RCC

#define STM32_GPIOC_BASE    0x480000800U    //GPIOC

#define STM32_RCC_AHB1ENR_OFFSET 0x0030  // AHB1 peripheral clock 

#define STM32_GPIO_MODER_OFFSET 0x0000 // GPIO port mode register 
#define STM32_GPIO_OTYPER_OFFSET 0x0004 // GPIO port output type register 
#define STM32_GPIO_PUPDR_OFFSET 0x000c // GPIO port pull-up/pull-down
#define STM32_GPIO_BSRR_OFFSET 0x0018 // GPIO reset register

#define STM32_RCC_AHB1ENR (STM32_RCC_BASE+STM32_RCC_AHB1ENR_OFFSET)
#define STM32_GPIOC_MODER (STM32_GPIOC_BASE+STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER (STM32_GPIOC_BASE+STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR (STM32_GPIOC_BASE+STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOC_BSRR (STM32_GPIOC_BASE + STM32_GPIO_BSRR_OFFSET)

#define STM32_RCC_AHB1ENR_GPIOCEN       (1 << 2)  //bit 2 porta C clock

        // GPIO MODE REGISTER
#define STM32_BOOT0_OUTPUT         			// output botao        
#define STM32_GPIO_MODER_INPUT     (0)     // input pino GPIO
#define STM32_GPIO_MODER_OUTPUT    (1)     // general output mode
#define STM32_GPIO_MODER_ALT       (2)     // alternative mode
#define STM32_GPIO_MODER_ANALOG    (3)     // analog mode

#define STM32_GPIO_MODER13_SHIFT   (26)    
#define STM32_GPIO_MODER13_MASK    (3 << STM32_GPIO_MODER13_SHIFT)

        // GPIO OUTPUT REGISTER

#define STM32_GPIO_OTYPER_PP       (0)     // output push-pull
#define STM32_GPIO_OTYPER_OD       (1)     // output open drain

#define STM32_GPIO_OT13_SHIFT      (13)
#define STM32_GPIO_OT13_MASK       (1 << STM32_GPIO_OT13_SHIFT)

        // GPIO PULL_UP/PULL_DOWN REGISTER

#define STM32_BOOT0_PULLUP         			// pull up
#define STM32_GPIO_PUPDR_NONE       (0)     // no pull-up
#define STM32_GPIO_PUPDR_PULLUP     (1)     // pull-up
#define STM32_GPIO_PUPDR_PULLDOWN   (2)     //pull-down

#define STM32_GPIO_PUPDR13_SHIFT    (26)    
#define STM32_GPIO_PUPDR13_MASK     (3 << STM32_GPIO_PUPDR13_SHIFT)

#define STM32_RCC_AHB1ENR_GPIOCEN       (1 << 2)  //bit 2 porta C clock

#define GPIO_BSRR_SET(n) (1 << (n))
#define GPIO_BSRR_RST(n) (1 << (n + 16))

static uint32_t led_status;
static const char     version [] = {'V', '1', '.', '0'};
int main (int argc, char *argv[])
{
    uint32_t reg;

    // Ponteiros para registradores 

    uint32_t *pRCC_AHB1ENR = (uint32_t *)STM32_RCC_AHB1ENR;
    uint32_t *pGPIOC_MODER = (uint32_t *)STM32_GPIOC_MODER;
    uint32_t *pGPIOC_OTYPER = (uint32_t *)STM32_GPIOC_OTYPER;
    uint32_t *pGPIOC_PUPDR = (uint32_t *)STM32_GPIOC_PUPDR;
    uint32_t *pGPIOC_BSRR = (uint32_t *)STM32_GPIOC_BSRR;

    // Habilita o clock no GPIOC

    reg = *pRCC_AHB1ENR;
    reg |= STM32_RCC_AHB1ENR_GPIOCEN;
    *pRCC_AHB1ENR = reg;

    // toda configuração da porta 13 como saida pull-up e pull-down off

    reg = *pGPIOC_MODER;
    reg &= ~(STM32_GPIO_MODER13_MASK);
    reg |= (STM32_GPIO_MODER_OUTPUT << STM32_GPIO_MODER13_SHIFT);
    *pGPIOC_MODER = reg;

    reg = *pGPIOC_OTYPER;
    reg &= ~(STM32_GPIO_OT13_MASK);
    reg |= (STM32_GPIO_OTYPER_PP << STM32_GPIO_OT13_SHIFT);
    *pGPIOC_OTYPER = reg;
    
    reg = *pGPIOC_PUPDR;
    reg &= ~(STM32_GPIO_PUPDR13_MASK);
    reg |= (STM32_GPIO_PUPDR_NONE << STM32_GPIO_PUPDR13_SHIFT);
    *pGPIOC_PUPDR = reg;


    while(1)
    {
        uint32_t LED_DELAY = 10;
        *pGPIOC_BSRR = GPIO_BSRR_SET(13);
        led_status = 0;
        for (uint32_t i = 0; i < LED_DELAY; i++);
        *pGPIOC_BSRR = GPIO_BSRR_RST(13);
        led_status = 1;
        for (uint32_t i = 0; i < LED_DELAY; i++);
    }

    return EXIT_SUCCESS;
}
