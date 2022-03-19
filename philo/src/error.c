/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:15 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:17 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage(void)
{
	printf("Usage: ./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosophers_must_eat]\n");
	return (-1);
}

int	error_args(void)
{
	printf("Non-positive integers parameters were passed to executable.\n");
	return (-1);
}

int	error_ll(void)
{
	printf("Arguments must be long long type.\n");
	return (-1);
}

int	general_error(void)
{
	printf("Error.\n");
	return (-1);
}

int	error_too_many(void)
{
	printf("Too many philosophers.\n");
	return (-1);
}
