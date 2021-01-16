/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:00:26 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 15:04:00 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		vabs(float i)
{
	return ((i >= 0) ? (i) : (i * (-1)));
}

int			calc_y(float h, float i)
{
	return ((int)((124 * (i - (Y_RES - h) / 2)) / h));
}

int			calc_x(float x)
{
	return ((((int)x * 2) % 128));
}

long		calc_rgb(int r, int g, int b)
{
	return (b + g * 256 + r * 65536);
}

int			ft_islimits(float *xy)
{
	if (!xy[1] || !xy[0] || !((int)xy[0] % 64) || !((int)xy[1] % 64)
		|| !(((int)xy[0] + 1) % 64) || !(((int)xy[1] + 1) % 64))
		return (1);
	return (0);
}
