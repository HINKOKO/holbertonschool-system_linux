#include <stdio.h>
#include <pthread.h>

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"

#define MAXCOUNT 1000000

void *thread_routine(void *data)
{
	/* each threads starts here*/
	pthread_t tid;
	unsigned int *count;
	unsigned int i = 0;

	tid = pthread_self();
	count = (unsigned int *)data;

	while (i < MAXCOUNT)
	{
		(*count)++;
		i++;
	}
	printf("Thread [%ld] finished. Final count is : %d\n", tid, *count);
	return (NULL);
}

int main(void)
{
	pthread_t tid1, tid2;
	unsigned int count = 0;

	/* each threads and 2 so expectation 2 * TIMESCOUNT */
	printf("Main: expected count is %s%u%s\n", GREEN, 2 * MAXCOUNT, RESET);
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("CReated first thread: [%ld]\n", tid1);

	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("CReated second thread: [%ld]\n", tid2);

	/* thread joining */
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if (count != (2 * MAXCOUNT))
		printf("%sMain: Error ! total count is %u%s\n", RED, count, RESET);
	else
		printf("%sMain: OK. total count is %u%s\n", GREEN, count, RESET);
	return (0);
}
