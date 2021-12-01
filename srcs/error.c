/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:15:33 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/29 16:07:15 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int	check_philo_args(int ac, char **av)
{
	int				i;
	int				j;
	long long int	tmp;

	if (ac < 5 || ac > 6)
		return (return_error("Usage:  \
number_of_philosophers  time_to_die  time_to_eat  time_to_sleep  \
[number_of_times_each_philosopher_must_eat]", 0, 0, 1));
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (return_error(av[i], "Numeric argument required", 0, 3));
		}
		tmp = ft_atoi(av[i]);
		if (tmp > 2147483647)
			return (return_error(av[i],
					"Number bigger than MAX_INT", 0, 2));
	}
	return (0);
}
