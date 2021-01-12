/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appah.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:41:43 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/11 17:42:43 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg(float x)
{
	return ((180 / PI) * x);
}

void	draw_sprite(int id)
{
	int		i;
	int		j;
	int		c;
	int		*l9alwa;
	float	size;

	i = -1;
	size = SP[id].size;
	l9alwa = (int*)TXTS.addr;
	while (++i < size - 1 && (j = -1))
	{
		if (SP[id].xof + i <= 0 || SP[id].xof + i >= X_RES)
			continue ;
		if (g_wall_distances[(int)(SP[id].xof + i)] <= SP[id].distance)
			continue ;
		while (++j < size - 1)
		{
			if (SP[id].yof + j <= 0 || SP[id].yof + j >= Y_RES)
				continue ;
			c = l9alwa[(int)((64) *
					(64 * j / (int)size) + (64 * i / (int)size))];
			if (c != l9alwa[0])
				my_mlx_pixel_put(&img, i + SP[id].xof, j + SP[id].yof, c);
		}
	}
}

void	to_sort(void)
{
	int				i;
	int				j;
	t_sprite		tmp;

	i = 0;
	while (i < g_nb_sprite - 1)
	{
		j = i;
		while (j < g_nb_sprite - 1)
		{
			if (SP[j].distance < SP[j + 1].distance)
			{
				tmp = SP[j];
				SP[j] = SP[j + 1];
				SP[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	to_sprite(void)
{
	float	angle;
	int		k;

	k = -1;
	to_sort();
	to_sort();
	angle = 0;
	while (++k < g_nb_sprite)
	{
		angle = atan2f(SP[k].y - Y_PLY, SP[k].x - X_PLY);
		while (angle - A_PLY > M_PI)
			angle -= 2 * M_PI;
		while (angle - A_PLY < -M_PI)
			angle += 2 * M_PI;
		SP[k].size = (float)((X_RES / SP[k].distance) * 64);
		SP[k].yof = (float)(Y_RES / 2 - SP[k].size / 2);
		SP[k].xof = (float)(((deg(angle) - deg(A_PLY)) * X_RES)
		/ 64 + ((X_RES / 2) - (int)SP[k].size / 2));
		draw_sprite(k);
	}
}
