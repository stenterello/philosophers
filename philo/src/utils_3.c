#include "philo.h"

void	left_handed(t_philos *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	pthread_mutex_lock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
}

void	right_handed(t_philos *philo)
{
	pthread_mutex_lock(&philo->r_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
	pthread_mutex_lock(&philo->l_fork->mutex);
	pthread_mutex_lock(&philo->context->writing);
	if (!philo->context->finished && !philo->context->some_die)
		printf("[%lu] %d has taken a fork\n", get_time(philo, 0) - philo->context->start_time, philo->id);
	pthread_mutex_unlock(&philo->context->writing);
}
