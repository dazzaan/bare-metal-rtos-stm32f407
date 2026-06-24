#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define TICKCOUNT        (84000U)
#define MAXTASK          (5U)

#define SCHD_STACK_SIZE  (1024U)
#define TASK_STACK_SIZE  (1024U)

#define SRAM_START       (0x20000000U)
#define SRAM_SIZE        (128U * 1024U)
#define SRAM_END         (SRAM_START + SRAM_SIZE)

#define T1_STACK_START   (SRAM_END)
#define T2_STACK_START   (SRAM_END - (1U * TASK_STACK_SIZE))
#define T3_STACK_START   (SRAM_END - (2U * TASK_STACK_SIZE))
#define T4_STACK_START   (SRAM_END - (3U * TASK_STACK_SIZE))
#define IDLE_STACK_START (SRAM_END - (4U * TASK_STACK_SIZE))
#define SCH_STACK_START  (SRAM_END - (5U * TASK_STACK_SIZE))

#define EXCEPTION_RETVAL (0xFFFFFFFDU)
#define DUMMY_XPSR       (0x01000000U)

#endif /* CONSTANTS_H_ */
