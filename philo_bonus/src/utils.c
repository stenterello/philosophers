/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:33:49 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:33:52 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	don_t_wake_cpu(t_philos *philo, uint64_t time)
{
	uint64_t	start;

	start = get_time(philo, 0) - philo->context->start_time;
	while (!philo->context->some_die)
	{
		if ((get_time(philo, 0) - philo->context->start_time) - start >= time)
			break ;
		usleep(10);
	}
}

void	write_message(t_philos *philo, int flag)
{
	sem_wait(philo->context->writing);
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
	sem_post(philo->context->writing);
}
