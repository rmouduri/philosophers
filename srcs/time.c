/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 23:47:18 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/01 12:33:00 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "philosophers.h"

void	ft_usleep(unsigned long long ms)
{
	unsigned long long	start_time;
	unsigned long long	curr_time;
	unsigned long long	end_time;

	start_time = get_elapsedtime();
	end_time = start_time + ms;
	while (1)
	{
		curr_time = get_elapsedtime();
		if (curr_time >= end_time)
			break ;
		usleep(100);
	}
}

unsigned long long	get_elapsedtime(void)
{
	static unsigned long long int	elapsedtime = 0;
	struct timeval					currtime;

	gettimeofday(&currtime, NULL);
	if (elapsedtime == 0)
		elapsedtime = currtime.tv_sec * 1000 + currtime.tv_usec / 1000;
	return ((currtime.tv_sec * 1000 + currtime.tv_usec / 1000) - elapsedtime);
}
