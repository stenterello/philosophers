#include "philo_bonus.h"

void	medea(t_philos *philos)
{
	int	i;
	int	ret;

	i = -1;
	if (philos[0].context->times_to_eat != -1)
		waitpid(-1, &ret, 0);
	else
		waitpid(0, &ret, 0);
	while (++i < philos[0].context->num_philos)
		kill(philos[i].pid, 15);
}

void	start_symposium(t_philos *philos)
{
	int	i;

	i = -1;
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
	sem_unlink("/going");
}