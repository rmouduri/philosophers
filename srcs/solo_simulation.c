/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:43:02 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/06 12:46:08 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*solo_simulation(t_philo *philo)
{
	print_state(FORK, philo, 0, 0);
	return (NULL);
}
