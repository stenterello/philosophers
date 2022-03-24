#include "philo_bonus.h"

void	usage(void)
{
	die("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosophers_must_eat]\n");
}

void	error_args(void)
{
	die("Non-positive integers parameters were passed to executable.\n");
}

void	error_ui(void)
{
	die("Arguments must be of unsigned integer type.\n");
}

void	general_error(void)
{
	die("Error.\n");
}

void	error_too_many(void)
{
	die("Too many philosophers.\n");
}
