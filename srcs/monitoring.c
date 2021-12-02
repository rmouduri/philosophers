/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:15:52 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/02 14:57:12 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philosophers.h"

static int	check_finished(t_info *info)
{
	int	i;

	i = -1;
	while (++i < (int)info->nb_of_philo)
	{
		pthread_mutex_lock(&info->ids_mutex[i]);
		if (info->ids[i])
		{
			pthread_mutex_unlock(&info->ids_mutex[i]);
			return (0);
		}
		pthread_mutex_unlock(&info->ids_mutex[i]);
	}
	return (1);
}

static void	close_all(t_philo *philos, t_info *info)
{
	int	i;

	i = -1;
	while (++i < (int)info->nb_of_philo)
		pthread_join(philos[i].thread, 0);
}

static int	end_all_simulations(int id, t_philo *philos, t_info *info)
{
	int	i;

	pthread_mutex_lock(&info->alive_mutex);
	info->alive = 0;
	pthread_mutex_unlock(&info->alive_mutex);
	print_state(IS_DEAD, &philos[id], 1, 0);
	i = -1;
	while (++i < (int)info->nb_of_philo)
	{
		if (i != id)
			pthread_join(philos[i].thread, NULL);
	}
	pthread_mutex_unlock(&info->ids_mutex[id]);
	pthread_join(philos[id].thread, NULL);
	return (1);
}

static int	check_thread(int id, t_philo *philos, t_info *info)
{
	unsigned long long	time;

	pthread_mutex_lock(&info->ids_mutex[id]);
	if (info->ids[id])
	{
		pthread_mutex_lock(&info->meal_mutex[id]);
		time = philos[id].last_meal
			+ (unsigned long long)info->time_to_die;
		pthread_mutex_unlock(&info->meal_mutex[id]);
		if (get_elapsedtime() >= time)
			return (end_all_simulations(id, philos, info));
	}
	pthread_mutex_unlock(&info->ids_mutex[id]);
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo				*philos;
	t_info				*info;
	int					id;

	philos = (t_philo *)arg;
	info = philos[0].info;
	while (1)
	{
		id = -1;
		while ((unsigned int)++id < info->nb_of_philo)
			if (check_thread(id, philos, info) != 0)
				return (NULL);
		if (check_finished(info) != 0)
		{
			close_all(philos, info);
			return (NULL);
		}
	}
	return (NULL);
}
