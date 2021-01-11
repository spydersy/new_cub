/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:49:10 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/11 17:40:48 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		vabs(float i)
{
	return ((i >= 0) ? (i) : (i * (-1)));
}

int		calc_y(float h, float i)
{
	return ((int)((124 * (i - (Y_RES - h) / 2)) / h));
}

int		calc_x(float x)
{
	return ((((int)x * 2) % 128));
}

void	build_wall(float dist, int c, int color, float x, float y)
{
	float					h;
	float					i;
	char					*dst;

	h = (64 * X_RES) / dist;
	g_wall_pix[c] = (Y_RES - h) / 2;
	i = -1;
	while (++i < (float)Y_RES)
	{
		if (i <= (float)((float)(Y_RES - h) / 2))
			my_mlx_pixel_put(&img, c, i, DATA.ce_color[2] + DATA.ce_color[1] * 256 + DATA.ce_color[0] * 65536);
		else if ((((float)Y_RES - h) / 2) < i && i < (((float)Y_RES + h) / 2))
		{
			if (color == 0x8934eb)
			{
				dst = TXT1.addr + (calc_y(h, i) * TXT1.line_length + calc_x(y) * (TXT1.bits_per_pixel / 8));
				my_mlx_pixel_put(&img, c, i, *(unsigned int*)dst);

			}
			else if (color == 0x34eb46)
			{
				dst = TXT3.addr + (calc_y(h, i) * TXT1.line_length + calc_x(x) * (TXT1.bits_per_pixel / 8));
				my_mlx_pixel_put(&img, c, i, *(unsigned int*)dst);
			}
			else if (color == 0xeb4034)
			{
				dst = TXT2.addr + (calc_y(h, i) * TXT1.line_length + calc_x(y) * (TXT1.bits_per_pixel / 8));
				my_mlx_pixel_put(&img, c, i, *(unsigned int*)dst);

			}
			else if (color == 0x34d0eb)
			{
				dst = TXT4.addr + (calc_y(h, i) * TXT1.line_length + calc_x(x) * (TXT1.bits_per_pixel / 8));
				my_mlx_pixel_put(&img, c, i, *(unsigned int*)dst);
			}
		}
		else
			my_mlx_pixel_put(&img, c, i, DATA.fl_color[2] + DATA.fl_color[1] * 256 + DATA.fl_color[0] * 65536);
	}
}

void	dda(float x0, float y0,  float x1, float y1, int color, int col)
{
	float		dx = x1 - x0;
	float		dy = y1 - y0;

	int		step = ((vabs(dx) > vabs(dy)) ? (vabs(dx)) : (vabs(dy)));

	float	xi = dx / (float)step;
	float	yi = dy / (float)step;

	float x = x0;
	float y = y0;

	int		i  = 0;

	if (color)
	{

	}

	static int	wcolor;
	while (i <= step)
	{
		if (!(((int)x + 1) % 64) && !(((int)y + 1) % 64) && (MAP[((int)y - 2) / 64][((int)x - 2) / 64] == '1' && MAP[((int)y + 2) / 64][((int)x + 2) / 64] == '1'))
		{
			dist = distance(X_PLY, Y_PLY, x, y);
			dist = dist * cos(vabs(g_player.current - A_PLY));
			g_wall_distances[col] = dist;
			build_wall(dist, col, wcolor, x, y);
			break;
		}
		else if (!(((int)x) % 64) && !(((int)y + 1) % 64) && (MAP[((int)y - 2) / 64][((int)x + 2) / 64] == '1' && MAP[((int)y + 2) / 64][((int)x - 2) / 64] == '1'))
		{
			dist = distance(X_PLY, Y_PLY, x, y);
			dist = dist * cos(vabs(g_player.current - A_PLY));
			g_wall_distances[col] = dist;
			build_wall(dist, col, wcolor, x, y);
			break;
		}
		else if (!(((int)x) % 64) && !(((int)y) % 64) && (MAP[((int)y - 2) / 64][((int)x + 2) / 64] == '1' && MAP[((int)y + 2) / 64][((int)x - 2) / 64] == '1'))
		{
			dist = distance(X_PLY, Y_PLY, x, y);
			dist = dist * cos(vabs(g_player.current - A_PLY));
			g_wall_distances[col] = dist;
			build_wall(dist, col, wcolor, x, y);
			break;
		}
		else if (!(((int)x + 1) % 64) && !(((int)y) % 64) && (MAP[((int)y - 2) / 64][((int)x - 2) / 64] == '1' && MAP[((int)y + 2) / 64][((int)x + 2) / 64] == '1'))
		{
			dist = distance(X_PLY, Y_PLY, x, y);
			dist = dist * cos(vabs(g_player.current - A_PLY));
			g_wall_distances[col] = dist;
			build_wall(dist, col, wcolor, x, y);
			break ;
		}
		else if (!y || !x || !((int)x % 64) || !((int)y % 64)
		|| !(((int)x + 1) % 64) || !(((int)y + 1) % 64))
		{
			if (MAP[(int)y / 64][(int)x / 64] == '1'
			|| MAP[(int)y / 64][(int)x / 64] == ' ')
			{
				if (!((int)x % 64) && ((int)y % 64) && (((int)y + 1) % 64))
					wcolor = 0x8934eb;
				else if (!((int)y % 64) && ((int)x % 64) && (((int)x + 1) % 64))
					wcolor = 0x34eb46;
				else if (!(((int)x + 1) % 64)
				&& ((int)y % 64) && (((int)y + 1) % 64))
					wcolor = 0xeb4034;
				else if (!(((int)y + 1) % 64)
				&& ((int)x % 64) && (((int)x + 1) % 64))
					wcolor = 0x34d0eb;
				dist = distance(X_PLY, Y_PLY, x, y);
				dist = dist * cos(vabs(g_player.current - A_PLY));
				g_wall_distances[col] = dist;
				build_wall(dist, col, wcolor, x, y);
				break ;
			}
			else if (MAP[(int)y / 64][(int)x / 64] == '2')
			{
				check_sprite(x, y);
			}
		}
		x += xi / 2;
		y += yi / 2;
		i++;
	}
}
