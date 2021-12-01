/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:32:57 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/01 16:37:24 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static int	get_nb_len(unsigned long long int n)
{
	int	i;

	i = 1;
	while (n >= 10)
	{
		++i;
		n /= 10;
	}
	return (i);
}

static int	add_n(char *str, unsigned long long int n)
{
	int	ret;
	int	len;
	int	i;

	len = get_nb_len(n);
	ret = len;
	i = len;
	while (--i >= 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}

void	print_state(char *state, t_philo *philo, char is_monitor)
{
	char	s[128];
	int		i;

	i = 0;
	pthread_mutex_lock(&philo->info->time_mutex);
	i += add_n(&s[i], get_elapsedtime());
	pthread_mutex_unlock(&philo->info->time_mutex);
	ft_strcpy(&s[i], ": ");
	i += 2;
	i += add_n(&s[i], philo->id);
	ft_strcpy(&s[i], state);
	i += ft_strlen(state);
	s[i] = 0;
	pthread_mutex_lock(&philo->info->write_mutex);
	if (is_monitor || (!is_monitor && is_alive(philo)))
		write(1, s, ft_strlen(s));
	pthread_mutex_unlock(&philo->info->write_mutex);
}
