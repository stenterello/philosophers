#include "philo.h"

int	usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosophers_must_eat]\n");
	return (-1);
}

int	error_args(void)
{
	printf("Non-positive integers parameters were passed to executable.\n");
	return (-1);
}

int	error_ints(void)
{
	printf("Arguments must be integers.\n");
	return (-1);
}

int	general_error(void)
{
	printf("Error.\n");
	return (-1);
}

int	error_too_many(void)
{
	printf("Too many philosophers.\n");
	return (-1);
}
