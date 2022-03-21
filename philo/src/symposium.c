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

void	*cycle(void *phi)
{
	t_philos	*philo;

	philo = (t_philos *)phi;
	pthread_mutex_lock(&philo->gen_mutex);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
		pthread_mutex_unlock(&philo->context->writing);
		pthread_mutex_lock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
		pthread_mutex_unlock(&philo->context->writing);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
		pthread_mutex_unlock(&philo->context->writing);
		pthread_mutex_lock(&philo->l_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
		pthread_mutex_unlock(&philo->context->writing);
	}
	pthread_mutex_lock(&philo->context->writing);
	printf("[%lu] %d is eating\n", get_time(philo, 1) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	usleep(philo->context->time_eat * 1000);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	printf("[%lu] %d is sleeping\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	usleep(philo->context->time_sleep * 1000);
	pthread_mutex_lock(&philo->context->writing);
	printf("[%lu] %d is thinking\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	pthread_mutex_unlock(&philo->gen_mutex);
	return (NULL);
}

int	find_dead_man(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].context->num_philos)
	{
		if (philos[i].dead)
			return (i + 1);
		i++;
	}
	return (0);
}

int	monitor_meals(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].context->num_philos)
	{
		if (philos[i].times_eaten < philos[i].context->times_to_eat)
			return (0);
		i++;
	}
	return (1);
}

void	print_info(t_philos *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].context->num_philos)
		printf("Il filosofo %d ha mangiato %d volte\n", philos[i].id, philos[i].times_eaten);
}

void	*monitor(void *philos)
{
	int			i;
	t_philos	*philo;

	philo = (t_philos *)philos;
	i = -1;
	while (++i < philo[0].context->num_philos)
	{
		if (get_time(&philo[i], 0) - philo[i].context->start_time - philo[i].last_meal > philo[0].context->time_die)
		{
			philo[i].context->some_die = 1;
			philo[i].dead = 1;
			return (NULL);
		}
	}
	if (philo[0].context->times_to_eat != -1)
		if (monitor_meals(philo))
			philo[0].context->finished = 1;
	return (NULL);
}

void	start_symposium(t_context *context, t_philos *philos)
{
	int	i;

	while (!context->some_die)
	{
		i = -1;
		while (++i < context->num_philos)
			pthread_create(&philos[i].thread, NULL, &cycle, &philos[i]);
		pthread_create(&context->monitor, NULL, &monitor, (void *)philos);
		if (context->some_die)
		{
			printf("[%lu] %d is dead\n", get_time(&philos[1], 0) - context->start_time, find_dead_man(philos));
			break ;
		}
		if (context->finished)
			break ;
	}
	i = 0;
	while (i < context->num_philos)
		pthread_mutex_destroy(&philos[i++].gen_mutex);
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
	print_info(philos);
	return (0);
}
