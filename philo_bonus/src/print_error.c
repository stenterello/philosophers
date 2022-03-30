/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelladi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:33:18 by ddelladi          #+#    #+#             */
/*   Updated: 2022/03/30 14:33:20 by ddelladi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void	die(char *str)
{
	ft_putendl_err(str);
	exit(-1);
}
