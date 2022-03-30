/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:33:00 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:33:01 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		sem_wait(philo->context->meal_check);
		if (get_time(philo, 0) - philo->context->start_time
			- philo->last_meal >= philo->context->time_die)
		{
			philo->context->some_die = 1;
			sem_wait(philo->context->writing);
			printf("%llu %d died\n", get_time(philo, 0)
				- philo->context->start_time, philo->id);
			exit(1);
		}
		sem_post(philo->context->meal_check);
		if (philo->context->times_to_eat != -1 && monitor_meals(philo))
			philo->context->finished = 1;
		usleep(500);
	}
	return (NULL);
}

void	take_fork(t_philos *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("%llu %d has taken a fork\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	sem_post(philo->context->writing);
}

void	born_child(t_philos *philo)
{
	pthread_create(&philo->context->monitor, NULL, &monitor, (void *)philo);
	while (!philo->context->some_die && !philo->context->finished)
	{
		take_fork(philo);
		if (philo->context->num_philos > 1)
			take_fork(philo);
		sem_wait(philo->context->meal_check);
		write_message(philo, 0);
		philo->times_eaten++;
		sem_post(philo->context->meal_check);
		don_t_wake_cpu(philo, philo->context->time_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		write_message(philo, 1);
		don_t_wake_cpu(philo, philo->context->time_sleep);
		write_message(philo, 2);
	}
	if (philo->context->some_die)
		exit(1);
	exit(0);
	return ;
}
