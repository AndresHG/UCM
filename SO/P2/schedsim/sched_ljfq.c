#include "sched.h"

/*
--Guillero Rius y Andrés Herranz
*/

int ljf_quantum=2;


struct ljf_data {
	int remaining_ticks_slice;
};

static int task_new_ljf_quant(task_t* t)
{
	struct ljf_data* cs_data=malloc(sizeof(struct ljf_data));

	if (!cs_data)
		return 1;  /* Cannot reserve memory */

	/* initialize the quantum */
	cs_data->remaining_ticks_slice=ljf_quantum;
	t->tcs_data=cs_data;
	return 0;
}

static void task_free_ljf_quant(task_t* t)
{
	if (t->tcs_data) {
		free(t->tcs_data);
		t->tcs_data=NULL;
	}
}

static task_t* pick_next_task_ljf_quant(runqueue_t* rq,int cpu)
{
	task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}

static int compare_tasks_cpu_burst(void *t1,void *t2)
{
	task_t* tsk1=(task_t*)t1;
	task_t* tsk2=(task_t*)t2;
	return tsk2->runnable_ticks_left-tsk1->runnable_ticks_left;
}

static void enqueue_task_ljf_quant(task_t* t,int cpu, int runnable)
{
	runqueue_t* rq=get_runqueue_cpu(cpu);
	struct ljf_data* cs_data=(struct ljf_data*) t->tcs_data;

	if (t->on_rq || is_idle_task(t))
		return;

	if (t->flags & TF_INSERT_FRONT) {
		//Clear flag
		t->flags&=~TF_INSERT_FRONT;
		sorted_insert_slist_front(&rq->tasks, t, 1, compare_tasks_cpu_burst);  //Push task
		cs_data->remaining_ticks_slice=ljf_quantum; // Reset slice
	} else{
		sorted_insert_slist(&rq->tasks, t, 1, compare_tasks_cpu_burst);  //Push task
		cs_data->remaining_ticks_slice=ljf_quantum; // Reset slice
	}

	/* If the task was not runnable before, update the number of runnable tasks in the rq*/
	if (!runnable) {
		task_t* current=rq->cur_task;

		/* Trigger a preemption if this task has a shorter CPU burst than current */
		if (preemptive_scheduler && !is_idle_task(current) && t->runnable_ticks_left>current->runnable_ticks_left) {
			rq->need_resched=TRUE;
			current->flags|=TF_INSERT_FRONT; /* To avoid unfair situations in the event
                                                another task with the same length wakes up as well*/
		}
	}
}

static void task_tick_ljf_quant(runqueue_t* rq,int cpu)
{
	task_t* current=rq->cur_task;
	struct ljf_data* cs_data=(struct ljf_data*) current->tcs_data;

	if (is_idle_task(current))
		return;

	cs_data->remaining_ticks_slice--; /* Charge tick */

	if (cs_data->remaining_ticks_slice<=0)
		rq->need_resched=TRUE; //Force a resched !!
}

static task_t* steal_task_ljf_quant(runqueue_t* rq,int cpu)
{
	task_t* t=tail_slist(&rq->tasks);

	if (t) {
		remove_slist(&rq->tasks,t);
		t->on_rq=FALSE;
		rq->nr_runnable--;
	}
	return t;
}


sched_class_t ljfq_sched= {
	.task_new=task_new_ljf_quant,
	.task_free=task_free_ljf_quant,
	.pick_next_task=pick_next_task_ljf_quant,
	.enqueue_task=enqueue_task_ljf_quant,
	.task_tick=task_tick_ljf_quant,
	.steal_task=steal_task_ljf_quant
};
