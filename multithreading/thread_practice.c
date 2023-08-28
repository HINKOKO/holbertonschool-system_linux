#include <stdio.h>
#include <pthread.h>

#define NC "\033[0m"
#define YELLOW "\033[33m"

void *thread_routine(void *data)
{
	pthread_t tid;

	(void)data;

	/* pthread_self() provides this thread's own ID */
	tid = pthread_self();
	printf(YELLOW "Thread [%ld]: The heaviest burden is to exist without living.%s\n", tid, NC);

	return (NULL); /* Thread ends here */
}

int main(void)
{
	pthread_t tid1; /* first thread id*/
	pthread_t tid2; /* second thread id*/

	/* creating first thread that will go execute its thread_routine function */
	pthread_create(&tid1, NULL, thread_routine, NULL);
	printf("Main: Created first thread [%ld]\n", tid1);
	/* creating second thread that will also exec thread_routine */
	pthread_create(&tid2, NULL, thread_routine, NULL);
	printf("Main: Created second thread [%ld]\n", tid2);

	/* main thread waits for the new threads to end with pthread_join */
	pthread_join(tid1, NULL);
	printf("Main: Joining first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joining second thread [%ld]\n", tid2);

	return (0);
}
