#ifndef GPIO_H_
#define GPIO_H_
#include<stdint.h>

// GPIOD Base
#define GPIOD_BASE      (0x40020C00UL)
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))
#define GPIOD_BSRR      (*(volatile uint32_t*)(GPIOD_BASE + 0x18))

// LED Pin definitions
#define LED_GREEN       12
#define LED_ORANGE      13
#define LED_RED         14
#define LED_BLUE        15

void gpio_init(void);
void toggle_led(uint8_t pin);
void led_on(uint8_t pin);
void led_off(uint8_t pin);

#endif
