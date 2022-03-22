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
	// Ciclo infinito del thread del filosofo
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
		usleep(philo->context->time_eat * 1000);
		pthread_mutex_unlock(&philo->l_fork->mutex);
		pthread_mutex_unlock(&philo->r_fork->mutex);
		pthread_mutex_lock(&philo->context->writing);
		write_message(philo, 1);
		pthread_mutex_unlock(&philo->context->writing);
		usleep(philo->context->time_sleep * 1000);
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
	while (!philo[0].context->finished && !philo[0].context->some_die)
	{
		i = -1;
		while (++i < philo[0].context->num_philos)
		{
			if (get_time(&philo[0], 0) - philo[0].context->start_time - philo[i].last_meal > philo[0].context->time_die)
			{
				philo[i].context->some_die = 1;
				philo[i].dead = 1;
				printf("[%lu] %d is dead\n", get_time(&philo[0], 0) - philo[0].context->start_time, philo[i].id);
				return (NULL);
			}
		}
		if (philo[0].context->times_to_eat != -1 && !philo[0].context->some_die)
		{
			if (monitor_meals(philo))
				philo[0].context->finished = 1;
		}
	}
	return (NULL);
}

void	start_symposium(t_context *context, t_philos *philos)
{
	int	i;

	// Inizializza i thread dei filosofi
	i = -1;
	while (++i < context->num_philos)
		pthread_create(&philos[i].thread, NULL, &cycle, &philos[i]);

	// Inizializza il thread di controllo
	pthread_create(&context->monitor, NULL, &monitor, (void *)philos);

	// Aspetta la fine del thread di controllo
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
	//print_info(philos);
	return (0);
}
