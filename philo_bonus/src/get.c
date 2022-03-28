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

void	get_philosophers(t_context *context, t_philos *philos, sem_t *forks)
{
	int		i;

	i = 0;
	while (i < context->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].context = context;
		philos[i].times_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].forks = forks;
		philos[i].is_dead = 0;
		i++;
	}
}

sem_t	*get_semaphores(t_context *context)
{
	sem_t	*ret;

	sem_unlink("/semaphore");
	ret = sem_open("/semaphore", O_CREAT, S_IRWXU, context->num_philos);
	return (ret);
}
