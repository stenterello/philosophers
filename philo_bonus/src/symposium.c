/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symposium.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:33:33 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:33:34 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	medea(t_philos *philos)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < philos[0].context->num_philos)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < philos[0].context->num_philos)
				kill(philos[i].pid, 15);
			break ;
		}
		i++;
	}
}

void	start_symposium(t_philos *philos)
{
	int	i;

	i = -1;
	philos[0].context->start_time = get_start_time();
	while (++i < philos[0].context->num_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			die("Fork error");
		if (!philos[i].pid)
			born_child(&philos[i]);
		usleep(50);
	}
	medea(philos);
	sem_close(philos[0].context->writing);
	sem_close(philos[0].forks);
	sem_unlink("/writing_sem");
	sem_unlink("/semaphore");
	sem_unlink("/meal_check");
}
