/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:33:26 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:33:27 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

uint64_t	get_time(t_philos *philo, int flag)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (flag)
		philo->last_meal = ((tv.tv_sec) * 1000 + \
			(tv.tv_usec) / 1000) - philo->context->start_time;
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000));
}

uint64_t	get_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
