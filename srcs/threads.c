/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:58:36 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/06 13:52:29 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "philosophers.h"

int	init_threads(t_philo *philos, int nb_of_philo)
{			
	int			i;
	pthread_t	sauron;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_create(&philos[i].thread, 0,
				(void *)(void *)&simulation, (void *)&philos[i]) != 0)
			return (return_error("Can't create even thread", 0, 0, 1));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < nb_of_philo)
	{
		if (pthread_create(&philos[i].thread, NULL,
				(void *)(void *)&simulation, (void *)&philos[i]) != 0)
			return (return_error("Can't create odd thread", 0, 0, 1));
		i += 2;
	}
	if (pthread_create(&sauron, NULL, &monitoring, (void *)philos) != 0)
		return (return_error("Can't create monitoring thread", 0, 0, 1));
	pthread_join(sauron, 0);
	return (0);
}
