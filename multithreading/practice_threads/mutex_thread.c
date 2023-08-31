#include <stdio.h>
#include <pthread.h>

#define TIMECOUNT 21000

#define RESET "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

typedef struct s_counter
{
	pthread_mutex_t count_mutex;
	unsigned int count;
} t_counter;

void *thread_routine(void *data)
{
	/* each threads starts here*/
	pthread_t tid;
	t_counter *counter; /* pointer to struct in main */
	unsigned int i;

	tid = pthread_self();
	counter = (t_counter *)data;

	pthread_mutex_lock(&counter->count_mutex);

	printf("%sThread [%ld]: Count at thread start: %u.%s\n", YELLOW, tid, counter->count, RESET);

	pthread_mutex_unlock(&counter->count_mutex);

	i = 0;
	while (i < TIMECOUNT)
	{
		/* Lock the mutex for the duration of incrementation */
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	/* print final count but do not forget to lock the mutex */
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Final count: %u.%s\n", BYELLOW, tid, counter->count, RESET);
	pthread_mutex_unlock(&counter->count_mutex);

	return (NULL);
}

int main(void)
{
	pthread_t tid1;
	pthread_t tid2;

	t_counter counter;
	/* var to keep trak of thread's count */
	counter.count = 0;

	/* init a mutex */
	pthread_mutex_init(&counter.count_mutex, NULL);
	/* each threads and 2 so expectation 2 * TIMESCOUNT */
	printf("Main: expected count is %s%u%s\n", GREEN, 2 * TIMECOUNT, RESET);
	/* create */
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("CReated first thread: [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("CReated second thread: [%ld]\n", tid2);
	/* thread joining */
	pthread_join(tid1, NULL);
	printf("Main: joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: joined second thread [%ld]\n", tid2);

	if (counter.count != (2 * TIMECOUNT))
		printf("%sMain: Error ! total count is %u%s\n", RED, counter.count, RESET);
	else
		printf("%sMain: OK. total count is %u%s\n", GREEN, counter.count, RESET);

	/* destroy the bathroom mutex lock dispositif special */
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}
