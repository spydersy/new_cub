/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:49:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 15:01:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		put_pixel_wall(int color, int c, float i, float *xy)
{
	char					*dst;
	float					h;

	h = (64 * X_RES) / g_wall_distances[c];
	if (color == 1)
		dst = TXT1.addr
		+ (calc_y(h, i) * TXT1.len + calc_x(xy[1]) * (TXT1.bpp / 8));
	else if (color == 2)
		dst = TXT3.addr
		+ (calc_y(h, i) * TXT1.len + calc_x(xy[0]) * (TXT1.bpp / 8));
	else if (color == 3)
		dst = TXT2.addr
		+ (calc_y(h, i) * TXT1.len + calc_x(xy[1]) * (TXT1.bpp / 8));
	else if (color == 4)
		dst = TXT4.addr
		+ (calc_y(h, i) * TXT1.len + calc_x(xy[0]) * (TXT1.bpp / 8));
	my_mlx_pixel_put(&img, c, i, *(unsigned int*)dst);
}

void		build_wall(int c, int color, float x, float y)
{
	float					h;
	float					i;
	float					xy[2];
	static long				wcolor;

	if (color > -1)
		wcolor = color;
	h = (64 * X_RES) / g_wall_distances[c];
	g_wall_pix[c] = (Y_RES - h) / 2;
	i = -1;
	xy[0] = x;
	xy[1] = y;
	while (++i < (float)Y_RES)
	{
		if (i <= (float)((float)(Y_RES - h) / 2))
			my_mlx_pixel_put(&img, c, i,
			calc_rgb(DATA.ce_color[0], DATA.ce_color[1], DATA.ce_color[2]));
		else if ((((float)Y_RES - h) / 2) < i && i < (((float)Y_RES + h) / 2))
		{
			put_pixel_wall(wcolor, c, i, xy);
		}
		else
			my_mlx_pixel_put(&img, c, i,
			calc_rgb(DATA.fl_color[0], DATA.fl_color[1], DATA.fl_color[2]));
	}
}

int			get_correct_color(float *xy, int col)
{
	static long wcolor;

	if (MAP[(int)xy[1] / 64][(int)xy[0] / 64] == '1')
	{
		if (!((int)xy[0] % 64)
		&& ((int)xy[1] % 64) && (((int)xy[1] + 1) % 64))
			wcolor = 1;
		else if (!((int)xy[1] % 64)
		&& ((int)xy[0] % 64) && (((int)xy[0] + 1) % 64))
			wcolor = 2;
		else if (!(((int)xy[0] + 1) % 64)
		&& ((int)xy[1] % 64) && (((int)xy[1] + 1) % 64))
			wcolor = 3;
		else if (!(((int)xy[1] + 1) % 64)
		&& ((int)xy[0] % 64) && (((int)xy[0] + 1) % 64))
			wcolor = 4;
		dist = dst(X_PLY, Y_PLY, xy[0], xy[1]);
		dist = dist * cos(vabs(P.crt - A_PLY));
		g_wall_distances[col] = dist;
		build_wall(col, wcolor, xy[0], xy[1]);
		return (1);
	}
	else if (MAP[(int)xy[1] / 64][(int)xy[0] / 64] == '2')
		check_sprite(xy[0], xy[1]);
	return (0);
}

int			init_dda(float *xy, float *dxy, float *xyi)
{
	int		step;

	xy[0] = X_PLY;
	xy[1] = Y_PLY;
	step = ((vabs(dxy[0]) > vabs(dxy[1])) ? (vabs(dxy[0])) : (vabs(dxy[1])));
	xyi[0] = dxy[0] / (float)step;
	xyi[1] = dxy[1] / (float)step;
	return (step);
}

void		dda(float x1, float y1, int col)
{
	float		dxy[2];
	int			step;
	float		xyi[2];
	float		xy[2];
	int			i;

	dxy[0] = x1 - X_PLY;
	dxy[1] = y1 - Y_PLY;
	step = init_dda(xy, dxy, xyi);
	i = -1;
	while (++i <= step)
	{
		if (ft_iswall(xy[0], xy[1]))
		{
			dist = dst(X_PLY, Y_PLY, xy[0], xy[1]) * cos(vabs(P.crt - A_PLY));
			g_wall_distances[col] = dist;
			build_wall(col, -1, xy[0], xy[1]);
			break ;
		}
		else if (ft_islimits(xy))
			if (get_correct_color(xy, col))
				break ;
		xy[0] += xyi[0] / 2;
		xy[1] += xyi[1] / 2;
	}
}
