/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:24 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:26 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(int argc, char **argv)
{
	t_context	context;

	context.num_philos = ft_atoi(argv[1]);
	context.time_die = ft_atoi(argv[2]);
	context.time_eat = ft_atoi(argv[3]);
	context.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		context.times_to_eat = ft_atoi(argv[5]);
	else
		context.times_to_eat = -1;
	context.some_die = 0;
	context.start_time = get_start_time();
	sit_at_table(&context);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (usage());
	else
	{
		if (checks(argc, argv) == -1)
			return (-1);
		if (philosophers(argc, argv) != 0)
			return (general_error());
	}
	return (0);
}
