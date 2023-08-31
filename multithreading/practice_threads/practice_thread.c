#include <stdio.h>
#include <pthread.h>

#define TIMECOUNT 21000

#define RESET "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

void *thread_routine(void *data)
{
	/* each threads starts here*/
	pthread_t tid;
	unsigned int *count; /* pointer to var in main*/
	unsigned int i;

	tid = pthread_self();
	count = (unsigned int *)data;
	printf("%sThread [%ld]: Count at thread start: %u.%s\n", YELLOW, tid, *count, RESET);

	i = 0;
	while (i < TIMECOUNT)
	{
		(*count)++;
		i++;
	}

	printf("%sThread [%ld]: Final count: %u.%s\n", BYELLOW, tid, *count, RESET);
	return (NULL);
}

int main(void)
{
	pthread_t tid1;
	pthread_t tid2;

	/* var to keep trak of thread's count */
	unsigned int count;

	count = 0;
	/* each threads and 2 so expectation 2 * TIMESCOUNT */
	printf("Main: expected count is %s%u%s\n", GREEN, 2 * TIMECOUNT, RESET);
	/* create */
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("CReated first thread: [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("CReated second thread: [%ld]\n", tid2);
	/* thread joining */
	pthread_join(tid1, NULL);
	printf("Main: joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: joined second thread [%ld]\n", tid2);

	if (count != (2 * TIMECOUNT))
		printf("%sMain: Error ! total count is %u%s\n", RED, count, RESET);
	else
		printf("%sMain: OK. total count is %u%s\n", GREEN, count, RESET);
	return (0);
}
