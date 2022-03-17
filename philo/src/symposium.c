#include "philo.h"

int	get_fork_id(int	i, t_context *context)
{
	if (i == -1)
		return (context->num_philos - 1);
	else if (i == context->num_philos)
		return (0);
	else
		return (i);
}

void	get_philosophers(t_context *context, t_philo philos[250], t_forks forks[500])
{
	int	i;

	i = 0;
	while (i < context->num_philos)
	{
		philos[i].id = i;
		philos[i].is_eating = 0;
		philos[i].is_sleeping = 0;
		philos[i].is_thinking = 0;
		philos[i].dead = 0;
		philos[i].hungry = 0;
		philos[i].context = context;
		philos[i].l_fork = &forks[get_fork_id(i - 1, context)];
		philos[i].l_fork = &forks[get_fork_id(i + 1, context)];
		i++;
	}
}

void	get_forks(t_context *context, t_forks forks[500])
{
	int	i;

	i = 0;
	while (i < context->num_philos * 2)
	{
		forks[i].id = i;
		forks[i].busy = 0;
		i++;
	}
}

int	sit_at_table(t_context *context)
{
	t_philo	philos[250];
	t_forks	forks[500];

	get_forks(context, &forks);
	get_philosophers(context, &philos, &forks);
	return (0);
}
