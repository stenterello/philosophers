/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:49 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:50 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(t_philos *philo, int flag)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (flag)
		philo->last_meal = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
