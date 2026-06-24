#include"constants.h"
#include"functiondecl.h"
#include"reg_mem_map.h"
#include"task.h"
#include"gpio.h"
int main(void)
{
	configure_faults();
	configure_clk();

	configure_tcb();
	configure_schdstack();

	configure_dummyframe();
	gpio_init();

	configure_systick(TICKCOUNT);
	start_task();



    while(1)
    {

    }
}
