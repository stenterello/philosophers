/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:31:01 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/23 18:31:09 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	left_handed(t_philos *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("%llu %d has taken a fork\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	pthread_mutex_lock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->meal_check);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("%llu %d has taken a fork\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
}

void	right_handed(t_philos *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("%llu %d has taken a fork\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	pthread_mutex_lock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->meal_check);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("%llu %d has taken a fork\n", get_time(philo, 0)
			- philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((*(str + i) > 8 && *(str + i) < 14) || *(str + i) == 32)
		i++;
	if (*(str + i) == 43 || *(str + i) == 45)
	{
		if (*(str + i) == 45)
			sign *= -1;
		i++;
	}
	if (*(str + i) == 43 || *(str + i) == 45)
		return (0);
	while (*(str + i) > 47 && *(str + i) < 58)
	{
		ret = (ret * 10) + (*(str + i) - 48);
		i++;
	}
	return (ret * sign);
}

void	kill_philo(t_philos *philo)
{
	philo->context->some_die = 1;
	pthread_mutex_lock(&philo[0].context->writing);
	printf("%llu %d died\n", get_time(&philo[0], 0)
		- philo[0].context->start_time, philo->id);
	return ;
}
