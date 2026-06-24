#include"constants.h"
#include"functiondecl.h"
#include"reg_mem_map.h"
#include"task.h"

TCB_t user_tasks[MAXTASK];
uint32_t current_task=0;
uint32_t time_ticks=0;

void flash_configure(void){
    FLASH_ACR &= ~0x7;          // Clear LATENCY bits [2:0]
    FLASH_ACR |= 2;            // Set Flash latency = 2 wait states

    FLASH_ACR |= (1U << 8);    // Enable Instruction Cache (ICEN)
    FLASH_ACR |= (1U << 9);    // Enable Data Cache (DCEN)
    FLASH_ACR |= (1U << 10);   // Enable Prefetch (PRFTEN)
}

void configure_clk(void){
    flash_configure();         // Configure Flash before increasing CPU clock

    RCC_CFGR |= (4 << 10);     // APB1 Prescaler = Divide by 2 (84MHz -> 42MHz)

    RCC_PLLCFGR =
        (16U  << 0)  |         // PLLM = 16  (16 MHz HSI / 16 = 1 MHz)
        (336U << 6)  |         // PLLN = 336 (1 MHz × 336 = 336 MHz VCO)
        (1U   << 16);          // PLLP = 4   (336 MHz / 4 = 84 MHz SYSCLK)

    RCC_CR |= (1U << 24);      // Enable PLL

    while (!(RCC_CR & (1U << 25))); // Wait until PLL locks (PLLRDY = 1)

    RCC_CFGR &= ~(3U << 0);    // Clear System Clock Switch bits (SW)

    RCC_CFGR |= (2U << 0);     // Select PLL as System Clock source

    while (((RCC_CFGR >> 2) & 0x3) != 0x2);
                                // Wait until PLL is actually used as SYSCLK
}
void configure_systick(uint32_t tickCount)
{
    STK_LOAD = tickCount - 1;   // Reload value. Counter counts from LOAD down to 0.

    STK_VAL  = 0;               // Clear the current counter value and COUNTFLAG. writing anything to this register clears register

    STK_CTRL = (1U << 0) |      // ENABLE: Start the SysTick timer.
               (1U << 1) |      // TICKINT: Enable SysTick interrupt on reaching 0.
               (1U << 2);       // CLKSOURCE: Use processor clock (HCLK) as clock source.
}

void configure_faults(void)
{
    SCB_SHCSR |= ((1U << 18) |   // Enable UsageFault
                  (1U << 17) |   // Enable BusFault
                  (1U << 16));   // Enable MemManage Fault

    SCB_CCR |= (1U << 4);        // Enable divide-by-zero trapping
}
void configure_tcb(void){
	for(uint32_t i=0;i<MAXTASK;i++){
			user_tasks[i].task_id=i+10;
			user_tasks[i].state=TASK_READY;
	}
	user_tasks[0].sp=(uint32_t*)IDLE_STACK_START;
	user_tasks[1].sp=(uint32_t*)T1_STACK_START;
	user_tasks[2].sp=(uint32_t*)T2_STACK_START;
	user_tasks[3].sp=(uint32_t*)T3_STACK_START;
	user_tasks[4].sp=(uint32_t*)T4_STACK_START;

	user_tasks[0].task_handler=idle_task_handler;
	user_tasks[1].task_handler=task1_handler;
	user_tasks[2].task_handler=task2_handler;
	user_tasks[3].task_handler=task3_handler;
	user_tasks[4].task_handler=task4_handler;


}
void configure_dummyframe(void){
	for(int i=0;i<MAXTASK;i++){
		uint32_t *pPSP=user_tasks[i].sp;

		*(--pPSP) = DUMMY_XPSR;
		*(--pPSP) = (uint32_t)user_tasks[i].task_handler;
		*(--pPSP) = EXCEPTION_RETVAL;


		for(int j=0;j<13;j++) *(--pPSP)=0;
		user_tasks[i].sp=(uint32_t*)pPSP;
	}

}


__attribute__((naked)) void configure_schdstack(void){
	__asm volatile(
	    "MSR MSP, %0\n"
	    :
	    : "r" (SCH_STACK_START)
	);
	__asm volatile (" BX LR");

}




__attribute__((naked)) void start_task(void)
{
    __asm volatile("SVC #0");
}
void svc_yield(void){
	SCB_ICSR|=(1U<<28);
}

__attribute__((naked)) void svc_start(void)
{
	 __asm volatile(
	       "BL     get_psp         \n"
	       "LDMIA  R0!, {R4-R11}   \n"
	       "MSR    PSP, R0         \n"
	       "LDR    LR, =0xFFFFFFFD \n"
	       "BX     LR              \n"
	   );
}

void SVC_Handler_Main(uint8_t svc_num)
{
    switch(svc_num)
    {
        case 0:
            svc_start();
            break;

        case 1:
            svc_yield();
            break;

        default:
            break;
    }
}

__attribute__((naked)) void SVC_Handler(void)
{
    __asm volatile(
        "TST    LR, #4        \n"
        "ITE    EQ            \n"
        "MRSEQ  R0, MSP       \n"
        "MRSNE  R0, PSP       \n"

        "LDR    R1, [R0, #24] \n"
        "LDRB   R0, [R1, #-2] \n"

        "B      SVC_Handler_Main \n"
    );
}

