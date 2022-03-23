#include "philo_bonus.h"

int	get_fork_id(int i, t_context *context)
{
	if (i == -1)
		return (context->num_philos - 1);
	else if (i == context->num_philos)
		return (0);
	else
		return (i);
}

void	get_philosophers(t_context *context, t_philos *philos, t_forks *forks)
{
	int	i;

	i = 0;
	while (i < context->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].context = context;
		philos[i].l_fork = &forks[get_fork_id(i + 1, context)];
		philos[i].r_fork = &forks[get_fork_id(i, context)];
		philos[i].times_eaten = 0;
		philos[i].last_meal = 0;
		i++;
	}
}

int	get_semaphores(t_forks *forks, t_context *context)
{
	int	i;

	i = -1;
	while (++i < context->num_philos)
	{
		forks[i].id = i;
		if (sem_init(&forks[i].sem, 1, 1) == -1);
			die("Initialize semaphores produced an error");
	}
}