#include "philo_bonus.h"

void	sit_at_table(t_context *context)
{
	t_philos	philos[250];
	sem_t		*forks;

	forks = get_semaphores(context);
	get_philosophers(context, philos, forks);
	start_symposium(philos);
}

void	philosophers(int argc, char **argv)
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
	sem_unlink("/writing_sem");
	context.writing = sem_open("/writing_sem", O_CREAT, S_IRWXU, 1);
	sem_unlink("/going");
	context.going = sem_open("/going", O_CREAT, S_IRWXU, 1);
	sit_at_table(&context);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		usage();
	else
	{
		checks(argc, argv);
		philosophers(argc, argv);
	}
	return (0);
}
