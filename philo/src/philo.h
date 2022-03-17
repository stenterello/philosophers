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
	int		num_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		times_to_eat;
}				t_context;

typedef struct s_forks
{
	int	id;
	int	busy;
}				t_forks;

typedef struct s_philo
{
	int			id;
	int			is_eating;
	int			is_sleeping;
	int			is_thinking;
	int			dead;
	int			hungry;
	t_context	*context;
	t_forks		*l_fork;
	t_forks		*r_fork;
	pthread_t	thread;
}				t_philo;

void	usage(void);
void	error_args(void);
void	error_ints(void);
void	general_error(void);
int		ft_atoi(const char *str);
int		checks(int argc, char **argv);
int		sit_at_table(t_context *context);

#endif
