/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:30:55 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/23 18:31:12 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
}

void	write_message(t_philos *philo, int flag)
{
	pthread_mutex_lock(&philo->context->writing);
	if (!flag && !philo->context->some_die && !philo->context->finished)
		printf("%lu %d is eating\n", get_time(philo, 1)
			- philo->context->start_time, philo->id);
	else if (flag == 1 && !philo->context->some_die
		&& !philo->context->finished)
		printf("%lu %d is sleeping\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	else if (flag == 2 && !philo->context->some_die
		&& !philo->context->finished)
		printf("%lu %d is thinking\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
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

	i = -1;
	while (++i < philos[0].context->num_philos)
	{
		if (philos[i].times_eaten < philos[i].context->times_to_eat)
			return (0);
	}
	return (1);
}
