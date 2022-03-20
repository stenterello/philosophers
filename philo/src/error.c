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
	write_error("Usage: ./philo number_of_philosophers ");
	write_error("time_to_die time_to_eat time_to_sleep ");
	write_error("[number_of_times_each_philosophers_must_eat]\n");
	return (-1);
}

int	error_args(void)
{
	write_error("Non-positive integers parameters were passed to executable.\n");
	return (-1);
}

int	error_ll(void)
{
	write_error("Arguments must be long long type.\n");
	return (-1);
}

int	general_error(void)
{
	write_error("Error.\n");
	return (-1);
}

int	error_too_many(void)
{
	write_error("Too many philosophers.\n");
	return (-1);
}
