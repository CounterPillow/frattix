#include "task.h"
#include "stdint.h"
#include "stdconst.h"

static task_t* first_task;
static task_t* last_task;

void tasks_schedule(void)
{
	task_t* current_task;	//Current task which is being handled
	task_t* next_task;	//Next task in the chain
	current_task = first_task;
	next_task = first_task;
	while(next_task != NULL)
	{
		//If our current task is less important than the next task, skip it.
		if(next_task->priority + next_task->skipped > current_task->priority + current_task->skipped)
		{
			current_task->skipped++;	//remember that we skipped the poor little guy
			current_task = next_task;	//skip him
		}
		next_task = current_task->task_after;	//Get our next task in the chain
		//HANDLE CURRENT_TASK HERE AND RESET ITS SKIPPED VALUE
	}
}

task_t* task_add(void)
{
	task_t new_task;
	//THIS IS A STUB
	if(&first_task == NULL)
	{
		*first_task = new_task;
	}
	*last_task = new_task;
	return &new_task;
}
