/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:36:12 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 14:58:29 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	res;
	int		nav;
	int		sign;

	nav = 0;
	sign = 1;
	res = 0;
	while (str[nav] == 32 || (str[nav] >= 9 && str[nav] <= 13 && str[nav]))
		nav++;
	while (str[nav] >= '0' && str[nav] <= '9')
	{
		if (res < 0 && sign < 0)
			return (0);
		else if (res < 0 && sign > 0)
			return (-1);
		res = res * 10 + str[nav++] - '0';
		if (res >= 2560)
			return (2560);
	}
	return (res * sign);
}
