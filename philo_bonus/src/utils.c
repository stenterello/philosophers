#include "philo_bonus.h"

void	ft_putchar_err(char c)
{
	write(2, &c, 1);
}

void	ft_putstr_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar_err(str[i++]);
}

void	ft_putendl_err(char *str)
{
	ft_putstr_err(str);
	ft_putchar_err('\n');
	exit(-1);
}

void	die(char *str)
{
	ft_putendl_err(str);
	exit(-1);
}

int	get_fork_id(int i, t_context *context)
{
	if (i == -1)
		return (context->num_philos - 1);
	else if (i == context->num_philos)
		return (0);
	else
		return (i);
}

void	get_philosophers(t_philos *philos, t_forks *forks, t_context *context)
{
	int	i;

	i = -1;
	while (++i < context->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].dead = 0;
		philos[i].last_meal = 0;
		philos[i].times_eaten = 0;
		philos[i].l_fork = &forks[get_fork_id(i + 1, context)];
		philos[i].r_fork = &forks[get_fork_id(i, context)];
		philos[i].context = context;
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
			return (-1);
	}
}
