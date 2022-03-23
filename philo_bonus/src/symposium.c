#include "philo_bonus.h"

void	born_child(t_philos *philo)
{}

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
		usleep(100);
	}
}