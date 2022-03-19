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

void	*eat(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		printf("[%llu] %d has taken a fork\n", get_time(philo, 0) - philo->context.start_time, philo->id);
		philo->is_blocked = 1;
		pthread_mutex_lock(&philo->r_fork->mutex);
		printf("[%llu] %d has taken a fork\n", get_time(philo, 0) - philo->context.start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		printf("[%llu] %d has taken a fork\n", get_time(philo, 0) - philo->context.start_time, philo->id);
		philo->is_blocked = 1;
		pthread_mutex_lock(&philo->l_fork->mutex);
		printf("[%llu] %d has taken a fork\n", get_time(philo, 0) - philo->context.start_time, philo->id);
	}
	philo->is_eating = 1;
	printf("[%llu] %d is eating\n", get_time(philo, 1) - philo->context.start_time, philo->id);
	usleep(philo->context.time_eat * 1000);
	philo->times_eaten++;
	philo->is_eating = 0;
	philo->is_blocked = 0;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	return (NULL);
}

void	*sleeping(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	philo->is_sleeping = 1;
	printf("[%llu] %d is sleeping\n", get_time(philo, 0) - philo->context.start_time, philo->id);
	usleep(philo->context.time_sleep * 1000);
	philo->is_sleeping = 0;
	return (NULL);
}

void	*thinking(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	philo->is_thinking = 1;
	printf("[%llu] %d is thinking\n", get_time(philo, 0) - philo->context.start_time, philo->id);
	usleep(philo->context.time_sleep * 1000);
	philo->is_thinking = 0;
	return (NULL);
}

int	monitor_meals(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].context.num_philos)
	{
		if (!philos[i].times_eaten)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *philos)
{
	int			i;
	t_philos	*philo;

	philo = (t_philos *)philos;
	i = -1;
	while (++i < philo[0].context.num_philos)
	{
		if (get_time(&philo[i], 0) - philo[i].last_meal > philo[0].context.time_die)
			philo[i].context.some_die = 1;
	}
	return (NULL);
}

int	find_dead_man(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].context.num_philos)
	{
		if (philos[i].dead)
			return (i + 1);
		i++;
	}
	return (0);
}

void	start_symposium(t_context *context, t_philos *philos)
{
	int	i;

	while (!context->some_die)
	{
		i = -1;
		while (++i < context->num_philos)
		{
			if (!philos[i].is_sleeping && !philos[i].is_eating && !philos[i].is_thinking)
			{
				pthread_create(&philos[i].thread, NULL, &eat, &philos[i]);
				usleep(100);
			}
		}
		i = -1;
		while (++i < context->num_philos)
		{
			if (!philos[i].is_sleeping && !philos[i].is_eating && !philos[i].is_thinking && !philos[i].is_blocked)
			{
				pthread_create(&philos[i].thread, NULL, &sleeping, &philos[i]);
				usleep(100);
			}
		}
		i = -1;
		while (++i < context->num_philos)
		{
			if (!philos[i].is_sleeping && !philos[i].is_eating && !philos[i].is_thinking && !philos[i].is_blocked)
			{
				pthread_create(&philos[i].thread, NULL, &thinking, &philos[i]);
				usleep(100);
			}
		}
		// while (++i < context->num_philos)
		// 	pthread_join(philos[i].thread, NULL);
		pthread_create(&context->monitor, NULL, &monitor, (void *)philos);
		pthread_join(context->monitor, NULL);
		if (context->some_die)
		{
			printf("[%llu] %d is dead\n", get_time(&philos[i], 0) - context->start_time, find_dead_man(philos));
			break ;
		}
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
	start_symposium(context, philos);
	kill_mutexes(forks, context);
	return (0);
}
