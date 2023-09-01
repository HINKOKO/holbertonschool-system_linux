#include "multithreading.h"
#include <stdlib.h>

/* mutex init as task 4 */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* this macro replace pthread_mutex_init() ?? */

/**
 * __attribute__((constructor)) void _initmut(void)
 * {
 *	pthread_mutex_init(&mutex, NULL);
 * }
 */


__attribute__((constructor)) void _destroy(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
 * create_task - create task dude !
 *
 * @entry: pointer to the entry function of the task
 * @param: param later be passed to entry function
 *
 * Return: pointer to the created task structure
 */

task_t *create_task(task_entry_t entry, void *param)
{
	task_t *creation = malloc(sizeof(task_t));

	if (!creation)
		return (NULL);

	creation->entry = entry;
	creation->param = param;
	creation->status = PENDING; /* default */
	creation->result = NULL;
	creation->lock = mutex; /* same trick as Task 4 */

	return (creation);
}

/**
 * destroy_task - destroy a task dude !
 *
 * @task: pointer to the task to be destroyed
 */

void destroy_task(task_t *task)
{
	free(task->result);
	free(task);
	return;
}

/**
 * exec_task - executes a task dude - Thread Entry

 * @tasks: pointer to the list of tasks to be executed
  -> each tasks in a node ?
 * Return: NULL can be returned safely, => its return value
 * won't be retrieved
 *
 * Challenge => Multiple threads will be going through the list of tasks,
 * and a task must be executed once only once only youu
 */

void *exec_tasks(list_t const *tasks)
{
	/* list_t linked with node_t , hence need some nodes to process */
	node_t *curr = NULL;
	task_t *task = NULL;
	size_t i = 0;


	/* task->head point to front node of list */
	curr = tasks->head;
	do {
		/* content is a 'custom content' linked to -> function pointer task_entry_t */
		/* it can point to any type => including a pointer to another structure */
		task = curr->content;
		pthread_mutex_lock(&mutex);
		/* default when created is => PENDING*/
		/* this is protecting from treatin again Task with another status too ?? */
		if (task->status == PENDING)
		{
			task->status = STARTED;
			/* tprintf take care already of pthread_self() printing thread_id */
			tprintf("[%02zd] Started\n", i);
			task->result = task->entry(task->param);
			/* task->entry : pointer to function */
			/* task->entry == prime_factors() param ? */
			/* param is hence : task->param (address to custom content to be passed)*/
			if (task->result)
				tprintf("[%02zd] Success\n", i);
			else
				tprintf("[%02zd] Failed\n", i);
		}
		pthread_mutex_unlock(&mutex);
		curr = curr->next;
		i++;

	} while (i < tasks->size);

	return (NULL);
}
