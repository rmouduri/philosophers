/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 13:38:58 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/06 13:47:52 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philosophers.h"

static void	check_forks(t_philo *philo, int id)
{
	if (!philo->lfork)
	{
		pthread_mutex_lock(&philo->info->forks_mutex[philo->id]);
		if (philo->info->forks[philo->id])
		{
			philo->info->forks[philo->id] = 0;
			++philo->forks;
			philo->lfork = 1;
			print_state(FORK, philo, 0, 0);
		}
		pthread_mutex_unlock(&philo->info->forks_mutex[philo->id]);
	}
	if (!philo->rfork)
	{
		pthread_mutex_lock(&philo->info->forks_mutex[id]);
		if (philo->info->forks[id])
		{
			philo->info->forks[id] = 0;
			++philo->forks;
			philo->rfork = 1;
			print_state(FORK, philo, 0, 0);
		}
		pthread_mutex_unlock(&philo->info->forks_mutex[id]);
	}
}

void	ph_get_forks(t_philo *philo)
{
	int	id;

	if (philo->id == philo->info->nb_of_philo - 1)
		id = 0;
	else
		id = philo->id + 1;
	while (is_alive(philo) && philo->forks != 2)
	{
		check_forks(philo, id);
		usleep(10);
	}
}
