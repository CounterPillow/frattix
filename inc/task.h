#ifndef TASK_H
#define TASK_H
#include "registers.h"
#include "stdint.h"
struct task_struct
{
	register_t registers;	//Registers of the task
	uint8_t priority;	//Priority
	uint32_t skipped;	//How many times the task hasn't been called by the scheduler
	struct task_struct* task_before;	//Double-Chained list
	struct task_struct* task_after;		//
};
typedef struct task_struct task_t;
#endif
