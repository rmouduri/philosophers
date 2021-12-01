/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:04:08 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/29 16:04:40 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int	return_error(char *s1, char *s2, char *s3, int ret)
{
	write(2, PROG_NAME, ft_strlen(PROG_NAME));
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
	{
		write(2, ": ", 2);
		write(2, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(2, ": ", 2);
		write(2, s3, ft_strlen(s3));
	}
	write(2, "\n", 1);
	return (ret);
}
