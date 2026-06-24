#include "gpio.h"
#include "reg_mem_map.h"

void gpio_init(void){
    // Enable GPIOD clock
    RCC_AHB1ENR |= (1U << 3);

    // Configure PD12, PD13, PD14, PD15 as output (01)
    // MODER has 2 bits per pin
    GPIOD_MODER &= ~((3U << 24) |   // clear PD12
                     (3U << 26) |   // clear PD13
                     (3U << 28) |   // clear PD14
                     (3U << 30));   // clear PD15

    GPIOD_MODER |=  ((1U << 24) |   // PD12 output
                     (1U << 26) |   // PD13 output
                     (1U << 28) |   // PD14 output
                     (1U << 30));   // PD15 output
}

void led_on(uint8_t pin){
    // BSRR lower 16 bits = set
    GPIOD_BSRR = (1U << pin);
}

void led_off(uint8_t pin){
    // BSRR upper 16 bits = reset
    GPIOD_BSRR = (1U << (pin + 16));
}

void toggle_led(uint8_t pin){
    GPIOD_ODR ^= (1U << pin);
}
