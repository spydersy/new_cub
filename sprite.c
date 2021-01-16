/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:15:08 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 14:56:11 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sprite(int id)
{
	int		i;
	int		j;
	int		c;
	int		*first_color;
	float	size;

	i = -1;
	size = SP[id].size;
	first_color = (int*)TXTS.addr;
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
			c = first_color[(int)((64) *
					(64 * j / (int)size) + (64 * i / (int)size))];
			if (c != first_color[0])
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
		while (angle - A_PLY > PI)
			angle -= 2 * PI;
		while (angle - A_PLY < -PI)
			angle += 2 * PI;
		SP[k].size = (float)((X_RES / SP[k].distance) * 64);
		SP[k].yof = (float)(Y_RES / 2 - SP[k].size / 2);
		SP[k].xof = (float)(((deg(angle) - deg(A_PLY)) * X_RES)
		/ 64 + ((X_RES / 2) - (int)SP[k].size / 2));
		draw_sprite(k);
	}
}

void	add_sprite(float x, float y)
{
	SP[g_nb_sprite].x_map = x / 64;
	SP[g_nb_sprite].y_map = y / 64;
	SP[g_nb_sprite].index = -1;
	SP[g_nb_sprite].x = SP[g_nb_sprite].x_map * 64 + 32;
	SP[g_nb_sprite].y = SP[g_nb_sprite].y_map * 64 + 32;
	SP[g_nb_sprite].distance = dst(X_PLY, Y_PLY,
	SP[g_nb_sprite].x, SP[g_nb_sprite].y);
	SP[g_nb_sprite].distance = SP[g_nb_sprite].distance
	* cos(vabs(P.crt - A_PLY));
	g_nb_sprite++;
}

int		check_sprite(float x, float y)
{
	int		x_position;
	int		y_position;
	int		i;

	x_position = x / 64;
	y_position = y / 64;
	i = -1;
	if (g_nb_sprite == 0)
	{
		add_sprite(x, y);
		return (0);
	}
	while (++i < g_nb_sprite)
	{
		if (x_position == SP[i].x_map && y_position == SP[i].y_map)
			return (0);
	}
	add_sprite(x, y);
	return (0);
}
