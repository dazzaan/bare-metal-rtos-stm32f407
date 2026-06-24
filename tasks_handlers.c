#include"constants.h"
#include"functiondecl.h"
#include"reg_mem_map.h"
#include"task.h"
#include"gpio.h"

void task1_handler(void){
    while(1){
        led_on(LED_GREEN);
        task_delay(1000);
        led_off(LED_GREEN);
        task_delay(1000);

    }
}
void task2_handler(void){
    while(1){
    	led_on(LED_ORANGE);
        task_delay(500);
        led_off(LED_ORANGE);
        task_delay(500);  // 0.5 second
    }
}
void task3_handler(void){
    while(1){
    	led_on(LED_RED);
        task_delay(250);
        led_off(LED_RED);
        task_delay(250); // 0.25 second
    }
}
void task4_handler(void){
    while(1){
    	led_on(LED_BLUE);
        task_delay(125);
        led_off(LED_BLUE);
        task_delay(125);// 0.125 second
    }
}
void idle_task_handler(void){
    while(1); // just spin
}
void yeild(void){
	user_tasks[current_task].state=TASK_BLOCKED;
	__asm volatile("SVC #1");
}

void update_status(void){
	if(user_tasks[current_task].state==TASK_RUNNING) user_tasks[current_task].state= TASK_READY;

}
uint32_t*  get_psp(void){
	return user_tasks[current_task].sp;
}

void switch_task(void){
	task_state_t  cstate=TASK_BLOCKED;
	for(int i=0;i<MAXTASK;i++){
		current_task++;
		current_task=current_task%MAXTASK;
		cstate=user_tasks[current_task].state;
		if(current_task!=0 && cstate==TASK_READY ){
			user_tasks[current_task].state=TASK_RUNNING;
			break;
		}
	}
	if(cstate==TASK_BLOCKED){
		current_task=0;
		user_tasks[current_task].state=TASK_RUNNING;
	}
}
void unblock_tasks(void){
    for(int i = 1; i < MAXTASK; i++){
        if(user_tasks[i].state == TASK_BLOCKED){
            if(time_ticks >= user_tasks[i].delay_ticks){
                user_tasks[i].state = TASK_READY;
            }
        }
    }
}
void save_psp(uint32_t* currPSP){
	user_tasks[current_task].sp=currPSP;
}
__attribute__((naked)) void PendSV_Handler(void){
	__asm volatile (" MRS R0, PSP           \n"
					" PUSH {LR}				\n"
			 	 	" STMDB R0!, {R4-R11}   \n"
					" BL save_psp           \n"
					" BL update_status		\n"
					" BL switch_task        \n"
					" BL get_psp			\n"
					" LDMIA R0!,{R4-R11}	\n"
					" MSR PSP,R0 			\n"
					"POP {LR}				\n"
					" BX LR   				\n" //for the time being this is not wrong i am leanring ;
	);
}

void SysTick_Handler(void){
	time_ticks++;
	unblock_tasks();
	SCB_ICSR|=(1U<<28);

}
void task_delay(uint32_t delay){
    if(current_task == 0) return;
    user_tasks[current_task].delay_ticks = time_ticks + delay;
    yeild();
}




void HardFault_Handler(void){
    while(1);
}
void MemManage_Handler(void){
    while(1);
}
void BusFault_Handler(void){
    while(1);
}
void UsageFault_Handler(void){
    while(1);
}
