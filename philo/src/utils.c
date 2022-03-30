/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:03:40 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:03:45 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork_id(int i, t_context *context)
{
	if (i == -1)
		return (context->num_philos - 1);
	else if (i == context->num_philos)
		return (0);
	else
		return (i);
}

void	get_philosophers(t_context *context, t_philos *philos, t_forks *forks)
{
	int	i;

	i = 0;
	while (i < context->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].context = context;
		philos[i].l_fork = &forks[get_fork_id(i + 1, context)];
		philos[i].r_fork = &forks[get_fork_id(i, context)];
		philos[i].times_eaten = 0;
		philos[i].last_meal = 0;
		pthread_mutex_init(&philos[i].meal_check, NULL);
		i++;
	}
}

void	get_mutexes(t_context *context, t_forks *forks)
{
	int	i;

	i = 0;
	while (i < context->num_philos * 2)
	{
		forks[i].id = i;
		i++;
	}
}

void	init_mutexes(t_forks *forks, t_context *context)
{
	int	i;

	i = 0;
	while (i < context->num_philos)
		pthread_mutex_init(&forks[i++].mutex, NULL);
	pthread_mutex_init(&context->writing, NULL);
}

void	kill_mutexes(t_forks *forks, t_context *context)
{
	int	i;

	i = 0;
	while (i < context->num_philos)
		pthread_mutex_destroy(&forks[i++].mutex);
	pthread_mutex_destroy(&context->writing);
}
