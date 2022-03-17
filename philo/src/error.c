#include "philo.h"

void	usage(void)
{
	printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosophers_must_eat]\n");
}

void	error_args(void)
{
	printf("Non-positive integers parameters were passed to executable.\n");
}

void	error_ints(void)
{
	printf("Arguments must be integers.\n");
}

void	general_error(void)
{
	printf("Error.\n");
}
