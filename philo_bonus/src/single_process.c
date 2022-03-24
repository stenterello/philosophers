#include "philo_bonus.h"

void	born_child(t_philos *philo)
{
	pthread_create(&philo->context->monitor, NULL, &monitor, (void *)philo);
	while (!philo->context->some_die && !philo->context->finished)
	{
		if (philo->id % 2)
			usleep(15000);
		// Prende le forchette
		sem_wait(philo->forks);
		if (!philo->context->finished && !philo->context->some_die)
			printf("%llu %d has taken a fork\n", get_time(philo, 0)
				- philo->context->start_time, philo->id);
		sem_wait(philo->forks);
		if (!philo->context->finished && !philo->context->some_die)
			printf("%llu %d has taken a fork\n", get_time(philo, 0)
				- philo->context->start_time, philo->id);
		// Mangia
		sem_wait(philo->context->writing);
		write_message(philo, 0);
		philo->times_eaten++;
		sem_post(philo->context->writing);
		don_t_wake_cpu(philo, philo->context->time_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		// Dorme
		sem_wait(philo->context->writing);
		write_message(philo, 1);
		sem_post(philo->context->writing);
		don_t_wake_cpu(philo, philo->context->time_sleep);
		// Pensa
		sem_wait(philo->context->writing);
		write_message(philo, 2);
		sem_post(philo->context->writing);
	}
	pthread_detach(philo->context->monitor);
	return ;
}