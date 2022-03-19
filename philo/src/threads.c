#include "philo.h"

void	eating_thread(t_philos *philo)
{
	printf("%d %d is eating\n", gettimeofday(), philo->id);
}

void	start_eat(t_philos *philo)
{
	pthread_create(&philo->thread, philo, &eating_thread, NULL);
}
