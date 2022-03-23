#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdint.h>
# include <semaphore.h>

typedef struct s_context
{
	int			num_philos;
	uint64_t	time_die;
	uint64_t	time_eat;
	uint64_t	time_sleep;
	int			times_to_eat;
	int			some_die;
	int			finished;
	uint64_t	start_time;
	sem_t		writing;
}				t_context;

typedef struct s_forks
{
	int		id;
	sem_t	sem;
}				t_forks;

typedef struct s_philos
{
	int			id;
	int			dead;
	uint64_t	last_meal;
	int			times_eaten;
	t_context	*context;
	t_forks		*l_fork;
	t_forks		*r_fork;
	
}				t_philos;

int	usage(void);
int	error_args(void);
int	error_ui(void);
int	general_error(void);
int	error_too_many(void);
int	checks(int argc, char **argv);

#endif
