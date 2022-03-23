#include "philo_bonus.h"

int	sit_at_table(t_context *context)
{
	t_philos	philos[250];
	t_forks		forks[250];

	if (get_sempahores(&forks, context) == -1)
		die("Semaphore initiation produced error");
	get_philosophers(&philos, &forks, context);
	

	return (0);
}

int	philosophers(int argc, char **argv)
{
	t_context	context;

	context.num_philos = ft_atoi(argv[1]);
	context.time_die = ft_atoi(argv[2]);
	context.time_eat = ft_atoi(argv[3]);
	context.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		context.times_to_eat = ft_atoi(argv[5]);
	else
		context.times_to_eat = -1;
	context.some_die = 0;
	context.start_time = get_start_time();
	context.finished = 0;
	sit_at_table(&context);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (usage());
	else
	{
		if (checks(argc, argv) == -1)
			return (-1);
		if (philosophers(argc, argv) != 0)
			return (general_error());
	}
	return (0);
}
