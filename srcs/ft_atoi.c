/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:18:21 by romain            #+#    #+#             */
/*   Updated: 2021/11/25 17:42:38 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int	ft_atoi(const char *str)
{
	int				sign;
	int				i;
	long long int	nb;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		++i;
	}
	return (nb * (long long int)sign);
}
