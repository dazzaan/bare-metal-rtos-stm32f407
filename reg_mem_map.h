#ifndef CORTEX_M_SYSTEM_REGS_H
#define CORTEX_M_SYSTEM_REGS_H

#define SCS_BASE                (0xE000E000UL)
#define SCB_BASE                (SCS_BASE + 0xD00UL)

#define SCB_ICSR                (*(volatile unsigned int*)(SCB_BASE + 0x04))
#define SCB_AIRCR               (*(volatile unsigned int*)(SCB_BASE + 0x0C))
#define SCB_CCR                 (*(volatile unsigned int*)(SCB_BASE + 0x14))
#define SCB_SHPR1               (*(volatile unsigned int*)(SCB_BASE + 0x18))
#define SCB_SHPR2               (*(volatile unsigned int*)(SCB_BASE + 0x1C))
#define SCB_SHPR3               (*(volatile unsigned int*)(SCB_BASE + 0x20))
#define SCB_SHCSR               (*(volatile unsigned int*)(SCB_BASE + 0x24))
#define SCB_CFSR                (*(volatile unsigned int*)(SCB_BASE + 0x28))

#endif



#define SYSTICK_BASE            (SCS_BASE + 0x10UL)

#define STK_CTRL                (*(volatile unsigned int*)(SYSTICK_BASE + 0x00))
#define STK_LOAD                (*(volatile unsigned int*)(SYSTICK_BASE + 0x04))
#define STK_VAL                 (*(volatile unsigned int*)(SYSTICK_BASE + 0x08))
#define STK_CALIB               (*(volatile unsigned int*)(SYSTICK_BASE + 0x0C))



#define FLASH_BASE              (0x40023C00)

#define FLASH_ACR 				(*(volatile unsigned int*)(FLASH_BASE+0x00))





#define RCC_BASE                (0x40023800UL)

/* RCC Registers */
#define RCC_CR                  (*(volatile unsigned int*)(RCC_BASE + 0x00))
#define RCC_PLLCFGR             (*(volatile unsigned int*)(RCC_BASE + 0x04))
#define RCC_CFGR                (*(volatile unsigned int*)(RCC_BASE + 0x08))
#define RCC_CIR                 (*(volatile unsigned int*)(RCC_BASE + 0x0C))

#define RCC_AHB1RSTR            (*(volatile unsigned int*)(RCC_BASE + 0x10))
#define RCC_AHB2RSTR            (*(volatile unsigned int*)(RCC_BASE + 0x14))
#define RCC_AHB3RSTR            (*(volatile unsigned int*)(RCC_BASE + 0x18))

#define RCC_APB1RSTR            (*(volatile unsigned int*)(RCC_BASE + 0x20))
#define RCC_APB2RSTR            (*(volatile unsigned int*)(RCC_BASE + 0x24))

#define RCC_AHB1ENR             (*(volatile unsigned int*)(RCC_BASE + 0x30))
#define RCC_AHB2ENR             (*(volatile unsigned int*)(RCC_BASE + 0x34))
#define RCC_AHB3ENR             (*(volatile unsigned int*)(RCC_BASE + 0x38))

#define RCC_APB1ENR             (*(volatile unsigned int*)(RCC_BASE + 0x40))
#define RCC_APB2ENR             (*(volatile unsigned int*)(RCC_BASE + 0x44))

#define RCC_AHB1LPENR           (*(volatile unsigned int*)(RCC_BASE + 0x50))
#define RCC_AHB2LPENR           (*(volatile unsigned int*)(RCC_BASE + 0x54))
#define RCC_AHB3LPENR           (*(volatile unsigned int*)(RCC_BASE + 0x58))

#define RCC_APB1LPENR           (*(volatile unsigned int*)(RCC_BASE + 0x60))
#define RCC_APB2LPENR           (*(volatile unsigned int*)(RCC_BASE + 0x64))

#define RCC_BDCR                (*(volatile unsigned int*)(RCC_BASE + 0x70))
#define RCC_CSR                 (*(volatile unsigned int*)(RCC_BASE + 0x74))

#define RCC_SSCGR               (*(volatile unsigned int*)(RCC_BASE + 0x80))
#define RCC_PLLI2SCFGR          (*(volatile unsigned int*)(RCC_BASE + 0x84))
