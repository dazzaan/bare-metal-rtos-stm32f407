
#include<stdint.h>
#ifndef TASK_H_
#define TASK_H_

typedef enum
{
    TASK_READY = 0,
    TASK_RUNNING,
    TASK_BLOCKED,
} task_state_t;

typedef struct
{
    uint32_t *sp;                 // Current PSP (required for context switching)

    uint32_t task_id;             // Unique task identifier
    uint32_t priority;            // Scheduler priority
    task_state_t state;           // Current task state

    uint32_t delay_ticks;         // Used by task_delay()

    void (*task_handler)(void);   // Task entry function

} TCB_t;

extern TCB_t user_tasks[MAXTASK];
extern uint32_t current_task;
extern uint32_t time_ticks;

#endif /* TASK_H_ */
