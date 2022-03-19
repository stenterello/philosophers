/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:05:30 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/19 16:05:32 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_context
{
	int			num_philos;
	uint64_t	time_die;
	uint64_t	time_eat;
	uint64_t	time_sleep;
	uint64_t	times_to_eat;
	int			some_die;
	int			all_eaten;
	uint64_t	start_time;
	pthread_t	monitor;
}				t_context;

typedef struct s_forks
{
	int				id;
	int				busy;
	pthread_mutex_t	mutex;
}				t_forks;

typedef struct s_philos
{
	int			id;
	int			is_eating;
	int			is_sleeping;
	int			is_thinking;
	int			is_blocked;
	int			dead;
	int			hungry;
	long		last_meal;
	int			times_eaten;
	t_context	context;
	t_forks		*l_fork;
	t_forks		*r_fork;
	pthread_t	thread;
}				t_philos;

int			usage(void);
int			error_args(void);
int			error_ll(void);
int			error_too_many(void);
int			general_error(void);
int			ft_atoi(const char *str);
int			checks(int argc, char **argv);
int			sit_at_table(t_context *context);
int			get_fork_id(int i, t_context *context);
void		get_philosophers(t_context *context, t_philos *philos, t_forks *forks);
void		get_mutexes(t_context *context, t_forks *forks);
void		init_mutexes(t_forks *forks, t_context *context);
void		kill_mutexes(t_forks *forks, t_context *context);
uint64_t	get_time(t_philos *philo, int flag);

#endif
