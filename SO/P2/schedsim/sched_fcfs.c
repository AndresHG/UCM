#include "sched.h"


static int task_new_fcfs(task_t* t)
{
	//Inecesaria
	return 0;
}

static void task_free_fcfs(task_t* t)
{
	if (t->tcs_data) {
		free(t->tcs_data);
		t->tcs_data=NULL;
	}
}

static task_t* pick_next_task_fcfs(runqueue_t* rq,int cpu)
{
	task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}

static void enqueue_task_fcfs(task_t* t,int cpu, int runnable)
{
	runqueue_t* rq=get_runqueue_cpu(cpu);

	if (t->on_rq || is_idle_task(t))
		return;

	insert_slist(&rq->tasks,t); //Push task
}

static void task_tick_fcfs(runqueue_t* rq,int cpu)
{
	task_t* current=rq->cur_task;

	if (is_idle_task(current))
		return;
}

static task_t* steal_task_fcfs(runqueue_t* rq,int cpu)
{
	task_t* t=tail_slist(&rq->tasks);

	if (t) 
		remove_slist(&rq->tasks,t);

	return t;
}

sched_class_t fcfs_sched= {
	.task_new=task_new_fcfs,
	.task_free=task_free_fcfs,
	.pick_next_task=pick_next_task_fcfs,
	.enqueue_task=enqueue_task_fcfs,
	.task_tick=task_tick_fcfs,
	.steal_task=steal_task_fcfs
};
