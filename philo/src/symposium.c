/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:36 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:37 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	don_t_wake_cpu(t_philos *philo, uint64_t time)
{
	uint64_t	start;

	start = get_time(philo, 0) - philo->context->start_time;
	while (!philo->context->some_die)
	{
		if ((get_time(philo, 0) - philo->context->start_time) - start >= time)
			break ;
		usleep(50);
	}
}

void	*cycle(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	while (!philo->context->finished && !philo->context->some_die)
	{
		if (philo->id % 2)
			left_handed(philo);
		else
			right_handed(philo);
		pthread_mutex_lock(&philo->context->writing);
		write_message(philo, 0);
		pthread_mutex_unlock(&philo->context->writing);
		philo->times_eaten++;
		don_t_wake_cpu(philo, philo->context->time_eat);
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		write_message(philo, 1);
		pthread_mutex_unlock(&philo->context->writing);
		don_t_wake_cpu(philo, philo->context->time_sleep);
		pthread_mutex_lock(&philo->context->writing);
		write_message(philo, 2);
		pthread_mutex_unlock(&philo->context->writing);
	}
	return (NULL);
}

void	*monitor(void *philos)
{
	int			i;
	t_philos	*philo;

	philo = (t_philos *)philos;
	while (!philo[0].context->finished)
	{
		i = -1;
		while (++i < philo[0].context->num_philos
			&& !philo[0].context->some_die)
		{
			if (get_time(&philo[0], 0) - philo[0].context->start_time
				- philo[i].last_meal > philo[0].context->time_die)
			{
				philo[i].context->some_die = 1;
				printf("%llu %d died\n", get_time(&philo[0], 0)
					- philo[0].context->start_time, philo[i].id);
				return (NULL);
			}
			usleep(50);
		}
		if (philo[0].context->times_to_eat != -1 && !philo[0].context->some_die
			&& monitor_meals(philo))
				philo[0].context->finished = 1;
	}
	return (NULL);
}

void	start_symposium(t_context *context, t_philos *philos)
{
	int	i;

	pthread_create(&context->monitor, NULL, &monitor, (void *)philos);
	i = -1;
	while (++i < context->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, &cycle, &philos[i]);
		usleep(100);
	}
	pthread_join(context->monitor, NULL);
}

int	sit_at_table(t_context *context)
{
	t_philos	philos[250];
	t_forks		forks[250];

	get_mutexes(context, forks);
	get_philosophers(context, philos, forks);
	init_mutexes(forks, context);
	start_symposium(context, philos);
	kill_mutexes(forks, context);
	return (0);
}
