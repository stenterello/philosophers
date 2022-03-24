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
	sem_t		*writing;
	sem_t		*going;
	pthread_t	monitor;
}				t_context;

typedef struct s_philos
{
	int			id;
	pid_t		pid;
	int			dead;
	uint64_t	last_meal;
	int			times_eaten;
	t_context	*context;
	sem_t		*forks;
}				t_philos;

void		usage(void);
void		error_args(void);
void		error_ui(void);
void		general_error(void);
void		error_too_many(void);
void		checks(int argc, char **argv);
void		get_philosophers(t_context *context, t_philos *philos, sem_t *forks);
sem_t		*get_semaphores(t_context *context);
uint64_t	get_start_time(void);
uint64_t	get_time(t_philos *philo, int flag);
void		start_symposium(t_philos *philos);
int			ft_atoi(const char *str);
void		ft_putchar_err(char c);
void		ft_putstr_err(char *str);
void		ft_putendl_err(char *str);
void		die(char *str);
int			monitor_meals(t_philos *philos);
void		*monitor(void *philos);
void		don_t_wake_cpu(t_philos *philo, uint64_t time);
void		write_message(t_philos *philo, int flag);
void		medea(t_philos *philos);
void		born_child(t_philos *philo);




#endif
