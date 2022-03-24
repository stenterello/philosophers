#include "philo_bonus.h"

int	monitor_meals(t_philos *philos)
{
	if (philos->times_eaten < philos->context->times_to_eat)
		return (0);
	return (1);
}

void	*monitor(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	while (!philo->context->finished)
	{
		if (get_time(philo, 0) - philo->context->start_time
			- philo->last_meal > philo->context->time_die)
		{
			philo->context->some_die = 1;
			philo->context->finished = 1;
			sem_wait(philo->context->writing);
			printf("%llu %d died\n", get_time(philo, 0)
				- philo->context->start_time, philo->id);
			return (NULL);
		}
		if (philo->context->times_to_eat != -1 && !philo->context->some_die
			&& monitor_meals(philo))
			philo[0].context->finished = 1;
	}
	kill(philo->pid, 15);
	sem_post(philo->context->going);
	return (NULL);
}