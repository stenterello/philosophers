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

// char    *ft_itoa(int n)
// {
//     char	*ret;
//     int		prov;
//     int		i;

//     i = 0;
// 	ret = malloc(sizeof(char) * 20);
//     prov = n;
//     if (n < 10)
//         ret[i] = (char)(n + 48);
//     else
//     {
//         while (n / 10)
//         {
//             ret[i++] = prov / 10 + 48;
//             prov = n % 10;
//             n /= 10;
//         }
// 		ret[i++] = prov + 48;
// 		ret[i] = '\0';
//     }
//     return (ret);
// }

// char	*sem_name(int n)
// {
// 	char	*base;
// 	char	*name;
// 	char	*ret;
// 	int		i;
// 	int		j;

// 	base = "/sem_";
// 	i = -1;
// 	ret = malloc(sizeof(char) * 20);
// 	while (base[++i])
// 		ret[i] = base[i];
// 	j = -1;
// 	name = ft_itoa(n);
// 	while (name[++j])
// 		ret[i++] = name[j];
// 	free(name);
// 	ret[i] = '\0';
// 	return (ret);
// }

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
		i++;
	}
}

sem_t	*get_semaphores(t_context *context)
{
	int		i;
	sem_t	*ret;

	i = -1;
	sem_unlink("/semaphore");
	ret = sem_open("/semaphore", O_CREAT, S_IRWXU, context->num_philos);
	return (ret);
}