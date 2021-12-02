/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:39:10 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/02 14:34:03 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

#include <pthread.h>
#include <stdlib.h>
#include "philosophers.h"

int	main(int ac, char **av)
{
	t_info		info;
	t_philo		*philos;

	philos = NULL;
	if (check_philo_args(ac, av) != 0)
		return (1);
	if (init_info(ac, av, &info) != 0
		|| info.nb_of_philo == 0 || info.must_eat == 0)
		return (2);
	if (init_philos(&info, &philos))
		return (free_structs(&info, philos));
	if (init_threads(philos, info.nb_of_philo) != 0)
		return (free_structs(&info, philos));
	free_structs(&info, philos);
	return (0);
}
