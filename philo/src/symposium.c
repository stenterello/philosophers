#include "philo.h"

void	*eat(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		printf("%ld philosopher %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->r_fork->mutex);
		printf("%ld philosopher %d has taken a fork\n", get_time(), philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		printf("%ld philosopher %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(&philo->l_fork->mutex);
		printf("%ld philosopher %d has taken a fork\n", get_time(), philo->id);
	}
	printf("%ld philosopher %d is eating\n", get_time(), philo->id);
	philo->last_meal = get_time();
	usleep(philo->context.time_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	return (NULL);
}

void	*sleeping(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	printf("%ld philosopher %d is sleeping\n", get_time(), philo->id);
	usleep(philo->context.time_sleep);
	return (NULL);
}

// void	*think(void *phi)
// {
// 	t_philos	*philo;

// 	philo = (t_philos *)phi;
// 	printf("%lld philosopher %d is thinking\n", get_time(), philo->id);
// 	usleep(philo->context.;
// 	return (NULL);
// }

void	start_symposium(t_context *context, t_philos *philos)
{
	int	i;

	i = -1;
	while (!context->some_die)
	{
		while (++i < context->num_philos)
			pthread_create(&philos[i].thread, NULL, &eat, &philos[i]);
		i = -1;
		while (++i < context->num_philos)
			pthread_join(philos[i].thread, NULL);
		i = -1;
		while (++i < context->num_philos)
			pthread_create(&philos[i].thread, NULL, &sleeping, &philos[i]);
		i = -1;
		// while (++i < context->num_philos)
		// 	pthread_join(philos[i].thread, NULL);
		// i = -1;
		//monitor_meals(philos);
	}
}



void	print_info(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].context.num_philos)
	{
		printf("Il filosofo %d, con fork_left: %d, fork_right %d\n", philos[i].id, philos[i].l_fork->id, philos[i].r_fork->id);
		i++;
	}
}



int	sit_at_table(t_context *context)
{
	t_philos	philos[250];
	t_forks		forks[250];

	get_mutexes(context, forks);
	get_philosophers(context, philos, forks);
	init_mutexes(forks, context);
	print_info(philos);
	start_symposium(context, philos);
	kill_mutexes(forks, context);
	return (0);
}
