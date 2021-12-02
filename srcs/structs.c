/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:48:25 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/29 15:20:47 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "philosophers.h"

int	free_structs(t_info *info, t_philo *philos)
{
	if (info->forks)
		free(info->forks);
	if (info->forks_mutex)
		free(info->forks_mutex);
	if (info->ids)
		free(info->ids);
	if (info->ids_mutex)
		free(info->ids_mutex);
	if (info->meal_mutex)
		free(info->meal_mutex);
	if (philos)
		free(philos);
	return (1);
}

int	init_philos(t_info *info, t_philo **philos)
{
	int	i;

	(*philos) = malloc(sizeof(t_philo) * (info->nb_of_philo));
	if (!(*philos))
	{
		free_structs(info, (*philos));
		return (return_error("Can't init t_philo struct",
				0, 0, 1));
	}
	i = -1;
	while (++i < (int)info->nb_of_philo)
	{
		(*philos)[i].info = info;
		(*philos)[i].thread = 0;
		(*philos)[i].id = i;
		(*philos)[i].has_eaten = 0;
		(*philos)[i].last_meal = 0;
	}
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	info->forks_mutex = malloc(sizeof(pthread_mutex_t) * (info->nb_of_philo));
	if (!info->forks_mutex)
		return (return_error("Can't init forks mutex tab", 0, 0, 3));
	i = -1;
	while (++i < (int)(info->nb_of_philo))
		pthread_mutex_init(&info->forks_mutex[i], NULL);
	info->meal_mutex = malloc(sizeof(pthread_mutex_t) * (info->nb_of_philo));
	if (!info->meal_mutex)
		return (return_error("Can't init meal mutex tab", 0, 0, 4));
	i = -1;
	while (++i < (int)(info->nb_of_philo))
		pthread_mutex_init(&info->meal_mutex[i], NULL);
	info->ids_mutex = malloc(sizeof(pthread_mutex_t) * (info->nb_of_philo));
	if (!info->ids_mutex)
		return (return_error("Can't init ids mutex tab", 0, 0, 5));
	i = -1;
	while (++i < (int)(info->nb_of_philo))
		pthread_mutex_init(&info->ids_mutex[i], NULL);
	pthread_mutex_init(&info->write_mutex, NULL);
	pthread_mutex_init(&info->alive_mutex, NULL);
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	info->nb_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = -1;
	info->alive = 1;
	info->ids = NULL;
	info->forks = NULL;
	info->ids_mutex = NULL;
	info->forks_mutex = NULL;
	info->meal_mutex = NULL;
	info->ids = malloc(sizeof(char) * info->nb_of_philo);
	if (!info->ids)
		return (return_error("Can't init ids tab", 0, 0, 1));
	memset(info->ids, 1, info->nb_of_philo);
	info->forks = malloc(sizeof(char) * info->nb_of_philo);
	if (!info->forks)
		return (return_error("Can't init forks tab", 0, 0, 2));
	memset(info->forks, 1, info->nb_of_philo);
	return (init_mutex(info));
}
