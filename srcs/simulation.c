/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:09:07 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/01 17:27:16 by rmouduri         ###   ########.fr       */
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
	print_state(SLEEPING, philo, 0);
	ft_usleep(philo->info->time_to_sleep);
}

void	ph_eat(t_philo *philo)
{
	int				id;

	pthread_mutex_lock(&philo->info->meal_mutex[philo->id]);
	philo->last_meal = get_elapsedtime();
	pthread_mutex_unlock(&philo->info->meal_mutex[philo->id]);
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
