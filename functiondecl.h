#include<stdint.h>

#ifndef FUNCTIONDECL_H_
#define FUNCTIONDECL_H_

void configure_faults(void);
void configure_clk(void);
void configure_systick(uint32_t tickCount);
void configure_tcb(void);
void configure_dummyframe(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void idle_task_handler(void);
__attribute__((naked)) void configure_schdstack(void);
void task_delay(uint32_t delay);
void unblock_tasks(void);
__attribute__((naked)) void start_task(void);



#endif /* FUNCTIONDECL_H_ */
