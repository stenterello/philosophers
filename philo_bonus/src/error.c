/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:32:30 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:32:31 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	usage(void)
{
	die("Usage: ./philo number_of_philosophers time_to_die \
		time_to_eat time_to_sleep \
		[number_of_times_each_philosophers_must_eat]");
}

void	error_args(void)
{
	die("Non-positive integers parameters were passed to executable.");
}

void	error_ui(void)
{
	die("Arguments must be of unsigned integer type.");
}

void	general_error(void)
{
	die("Error.");
}

void	error_too_many(void)
{
	die("Too many philosophers.");
}
