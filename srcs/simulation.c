/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:09:07 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/01 17:03:10 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosophers.h"

int	is_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->info->alive_mutex);
	alive = philo->info->alive;
	pthread_mutex_unlock(&philo->info->alive_mutex);
	return (alive);
}

void	ph_sleep(t_philo *philo)
{
	if (is_alive(philo))
		print_state(SLEEPING, philo, 0);
	ft_usleep(philo->info->time_to_sleep);
}

void	ph_eat(t_philo *philo)
{
	int				id;

	pthread_mutex_lock(&philo->info->meal_mutex[philo->id]);
	philo->last_meal = get_elapsedtime();
	pthread_mutex_unlock(&philo->info->meal_mutex[philo->id]);
	if (is_alive(philo))
		print_state(EATING, philo, 0);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->id]);
	philo->info->forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->id]);
	if (philo->id == philo->info->nb_of_philo - 1)
		id = 0;
	else
		id = philo->id + 1;
	pthread_mutex_lock(&philo->info->forks_mutex[id]);
	philo->info->forks[id] = 1;
	pthread_mutex_unlock(&philo->info->forks_mutex[id]);
	++philo->has_eaten;
	philo->forks = 0;
}

void	ph_check_fork(t_philo *philo)
{
	int	id;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->id]);
	if (philo->info->forks[philo->id])
	{
		philo->info->forks[philo->id] = 0;
		++philo->forks;
		if (is_alive(philo))
			print_state(FORK, philo, 0);
	}
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->id]);
	if (philo->id == philo->info->nb_of_philo - 1)
		id = 0;
	else
		id = philo->id + 1;
	pthread_mutex_lock(&philo->info->forks_mutex[id]);
	if (philo->info->forks[id])
	{
		philo->info->forks[id] = 0;
		++philo->forks;
		if (is_alive(philo))
			print_state(FORK, philo, 0);
	}
	pthread_mutex_unlock(&philo->info->forks_mutex[id]);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id == 0)
		get_elapsedtime();
	while (is_alive(philo) && (philo->info->must_eat == -1
			|| ((int)philo->has_eaten < philo->info->must_eat)))
	{
		ph_check_fork(philo);
		if (philo->forks == 2)
		{
			ph_eat(philo);
			if ((philo->info->must_eat != -1
					&& (int)philo->has_eaten >= philo->info->must_eat))
				break ;
			ph_sleep(philo);
			print_state(THINKING, philo, 0);
		}
	}
	pthread_mutex_lock(&philo->info->ids_mutex[philo->id]);
	philo->info->ids[philo->id] = 0;
	pthread_mutex_unlock(&philo->info->ids_mutex[philo->id]);
	return (NULL);
}

int		check_finished(t_info *info)
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

void	close_all(t_philo *philos, t_info *info)
{
	int	i;

	i = -1;
	// while (++i < (int)info->nb_of_philo)
		// if (info->ids[i])
			// pthread_detach(philos[i].thread);
	i = -1;
	while (++i < (int)info->nb_of_philo)
		pthread_join(philos[i].thread, 0);
}

void	*monitoring(void *arg)
{
	t_philo				*philos;
	t_info				*info;
	int					id;
	unsigned long long	time;

	philos = (t_philo *)arg;
	info = philos[0].info;
	while (1)
	{
		id = -1;
		while ((unsigned int)++id < info->nb_of_philo)
		{
			pthread_mutex_lock(&info->ids_mutex[id]);
			if (info->ids[id])
			{
				pthread_mutex_lock(&info->meal_mutex[id]);
				time = philos[id].last_meal
					+ (unsigned long long)info->time_to_die;
				pthread_mutex_unlock(&info->meal_mutex[id]);
				if (get_elapsedtime() >= time)
				{
					pthread_mutex_lock(&info->alive_mutex);
					info->alive = 0;
					pthread_mutex_unlock(&info->alive_mutex);
					// pthread_mutex_lock(&info->write_mutex);
					print_state(IS_DEAD, &philos[id], 1);
					for(int i = 0; i < (int)info->nb_of_philo; ++i)
					{
						// while (1);
						// printf("id = %d\n", id);
						// if (info->ids[i])
							// pthread_detach(philos[i].thread);
						// printf("Waiting for %d\n", i);
						if (i != id)
						pthread_join(philos[i].thread, NULL);
					}
					// pthread_mutex_unlock(&info->write_mutex);
					pthread_mutex_unlock(&info->ids_mutex[id]);
					pthread_join(philos[id].thread, NULL);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&info->ids_mutex[id]);
		}
		if (check_finished(info) != 0)
		{
			close_all(philos, info);
			return (NULL);
		}
	}
	return (NULL);
}
