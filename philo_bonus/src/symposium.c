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

void	print_info(t_philos *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].context->num_philos)
	{
		printf("Il filosofo %d ha mangiato %d volte\n", philos[i].id, philos[i].times_eaten);
	}
}

void	start_symposium(t_philos *philos)
{
	int	i;

	i = -1;
	sem_wait(philos[0].context->going);
	while (++i < philos[0].context->num_philos)
	{
		philos[i].pid = fork();
		if (philos[i].pid < 0)
			die("Fork error");
		if (!philos[i].pid)
			born_child(&philos[i]);
		usleep(50);
	}
	sem_wait(philos[0].context->going);
	i = -1;
	while (++i < philos[0].context->num_philos)
		kill(philos[i].pid, 15);
	sem_close(philos[0].context->writing);
	sem_close(philos[0].forks);
	sem_unlink("/writing_sem");
	sem_unlink("/semaphore");
	
}