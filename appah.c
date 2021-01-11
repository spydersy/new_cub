#include "cub3d.h"

float	deg(float x)
{
	return ((180 / M_PI) * x);
}

void	draw_sprite(int id)
{
	int		i;
	int		j;
	int		c;
	int		*l9alwa;
	float	size;

	i = -1;
	size = g_sp[id].size;
	l9alwa = (int*)g_txts.addr;
	while (++i < size - 1 && (j = -1))
	{
		if (g_sp[id].xof + i <= 0 || g_sp[id].xof + i > X_RES - 1)
			continue ;
		if (g_wall_distances[(int)(g_sp[id].xof + i)] <= g_sp[id].distance)
			continue ;
		while (++j < size - 1)
		{
			if (g_sp[id].yof + j <= 0 || g_sp[id].yof + j > Y_RES - 1)
				continue ;
			c = l9alwa[(int)((64) *
					(64 * j / (int)size) + (64 * i / (int)size))];
			if (c != l9alwa[0])
				my_mlx_pixel_put(&img, i + g_sp[id].xof, j + g_sp[id].yof, c);
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
			if (g_sp[j].distance < g_sp[j + 1].distance)
			{
				tmp = g_sp[j];
				g_sp[j] = g_sp[j + 1];
				g_sp[j + 1] = tmp;
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
		angle = atan2f(g_sp[k].y - g_player.y, g_sp[k].x - g_player.x);
		while (angle - g_player.rotation > M_PI)
			angle -= 2 * M_PI;
		while (angle - g_player.rotation < -M_PI)
			angle += 2 * M_PI;
		g_sp[k].size = (float)((X_RES / g_sp[k].distance) * 64);
		g_sp[k].yof = (float)(Y_RES / 2 - g_sp[k].size / 2);
		g_sp[k].xof = (float)(((deg(angle) - deg(g_player.rotation)) * X_RES)
		/ 64 + ((X_RES / 2) - (int)g_sp[k].size / 2));
		draw_sprite(k);
	}
}
