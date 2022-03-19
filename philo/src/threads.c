/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:42 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:43 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_thread(t_philos *philo)
{
	printf("%d %d is eating\n", gettimeofday(), philo->id);
}

void	start_eat(t_philos *philo)
{
	pthread_create(&philo->thread, philo, &eating_thread, NULL);
}
