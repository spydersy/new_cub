/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:59:23 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 10:01:08 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		normalize(float angle)
{
	while (angle < 0)
		angle += PI * 2;
	while (angle >= PI * 2)
		angle -= PI * 2;
	return (angle);
}

float		distance(float x0, float y0, float x1, float y1)
{
	float		distance;

	distance = sqrtf((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
	return (distance);
}

int			ft_iscollision(float *xy, float *xyi)
{
	if (!xy[1] || !xy[0] || !((int)xy[0] % 64) || !((int)xy[1] % 64)
	|| !(((int)xy[0] + 1) % 64) || !(((int)xy[1] + 1) % 64))
	{
		if (MAP[(int)xy[1] / 64][(int)xy[0] / 64] == '1'
		|| MAP[(int)xy[1] / 64][(int)xy[0] / 64] == ' '
		|| MAP[(int)xy[1] / 64][(int)xy[0] / 64] == '2')
		{
			X_PLY = xy[0] - 10 * xyi[0];
			Y_PLY = xy[1] - 10 * xyi[1];
			return (1);
		}
	}
	return (0);
}

void		get_new_position(float x1, float y1, int nb_steps)
{
	float	dxy[2];
	float	xyi[2];
	int		step;
	float	xy[2];
	int		i;

	dxy[0] = x1 - X_PLY;
	dxy[1] = y1 - Y_PLY;
	step = ((vabs(dxy[0]) > vabs(dxy[1])) ? (vabs(dxy[0])) : (vabs(dxy[1])));
	xyi[0] = dxy[0] / (float)step;
	xyi[1] = dxy[1] / (float)step;
	xy[0] = X_PLY;
	xy[1] = Y_PLY;
	i = 0;
	nb_steps = ((nb_steps <= step) ? (nb_steps) : (step));
	while (i <= nb_steps)
	{
		if (ft_iscollision(xy, xyi))
			break ;
		xy[0] += xyi[0];
		xy[1] += xyi[1];
		i++;
		X_PLY = xy[0] - xyi[0];
		Y_PLY = xy[1] - xyi[1];
	}
}

int			ft_cast_rays(void)
{
	int		step;
	float	teta;

	step = -1;
	teta = PI / (3 * X_RES);
	g_player.current = A_PLY;
	A_PLY = A_PLY - PI / 6;
	while (++step < X_RES)
	{
		dda(
		(int)(X_PLY + cosf(A_PLY) * 100000000),
		(int)(Y_PLY + sinf(A_PLY) * 100000000), step);
		A_PLY += teta;
	}
	A_PLY = g_player.current;
	to_sprite();
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.win, img.img, 0, 0);
	return (0);
}
