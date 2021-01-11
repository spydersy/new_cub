/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:52:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/09 17:18:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		normalize(float angle)
{
	while (angle < 0)
		angle += PI * 2;
	while (angle >= PI * 2)
		angle -= PI * 2;
	return angle;
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

float	distance(float x0, float y0, float x1, float y1)
{
	float		distance;

	distance = sqrtf((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
	return (distance);
}


void	draw_map(int y_max, int x_max)
{
	int			x;
	int			y;


	y = -1;
	while (++y < y_max)
	{
		x = -1;
		while (++x < x_max)
		{
			if (ft_isalpha(g_map[y][x]))
			{
				g_player.x = x * 64 + 32;
				g_player.y = y * 64 + 32;
			}
		}
	}
}

void	get_new_position(float x0, float y0, float x1, float y1, int nb_steps)
{
	float		dx = x1 - x0;
	float		dy = y1 - y0;

	int		step = ((vabs(dx) > vabs(dy)) ? (vabs(dx)) : (vabs(dy)));

	float	xi = dx / (float)step;
	float	yi = dy / (float)step;

	float x = x0;
	float y = y0;

	int		i = 0;
	nb_steps =((nb_steps <= step) ? (nb_steps) : (step));
	while (i <= nb_steps)
	{
		if (!y || !x || !((int)x % 64) || !((int)y % 64) || !(((int)x + 1) % 64) || !(((int)y + 1) % 64))
		{
			if (g_map[(int)y / 64][(int)x / 64] == '1' || g_map[(int)y / 64][(int)x / 64] == ' ' || g_map[(int)y / 64][(int)x / 64] == '2')
			{
				g_player.x = x - 10 * xi;
				g_player.y = y - 10 * yi;
				break;
			}
		}
		x += xi;
		y += yi;
		i++;
		g_player.x = x - xi;
		g_player.y = y - yi;
	}
}

void	ft_move_v(int direction)
{
	get_new_position(
	g_player.x,
	g_player.y,
	(g_player.x + (direction * -1) * cosf(g_player.rotation) * 100000000),
	(g_player.y + (direction * -1) * sinf(g_player.rotation) * 100000000), 40);
}

void	ft_move_h(int direction)
{
	get_new_position(g_player.x,
		g_player.y,
		(g_player.x + (direction) * cosf(g_player.rotation + PI / 2) * 100000000),
		(g_player.y + (direction) * sinf(g_player.rotation + PI / 2) * 100000000), 18);
}

void	malloc_sprite(void)
{
	if (g_sprite != NULL)
		free(g_sprite);
	if (!(g_sprite = malloc(sizeof(t_sprite) * 100)))
		ft_error("malloc\n");
	g_nb_sprite = 0;
}

void	ft_new_frame(int key)
{
	mlx_clear_window(g_mlx.mlx, g_mlx.win);
	if (key == L_KEY)
		g_player.rotation = g_player.rotation  - PI / 40;
	if (key == R_KEY)
		g_player.rotation = g_player.rotation  + PI / 40;
	if (key == W_KEY)
		ft_move_v(-1);
	if (key == S_KEY)
		ft_move_v(1);
	if (key == A_KEY)
		ft_move_h(-1);
	if (key == D_KEY)
		ft_move_h(1);	
	if (key == L_KEY || key == R_KEY)
		g_player.rotation = normalize(g_player.rotation);
}

int		ft_cast_rays()
{
	int		step;
	float	teta;
	
	step = -1;
	teta = PI / (3 * g_data.resolution[0]);
	g_player.current = g_player.rotation;
	g_player.rotation = g_player.rotation - PI / 6;
	while (++step < g_data.resolution[0])
	{
		dda(g_player.x,
		g_player.y,
		(int)(g_player.x + cosf(g_player.rotation) * 100000000),
		(int)(g_player.y + sinf(g_player.rotation) * 100000000), 0XFF0000, step);
		g_player.rotation += teta;
	}
	g_player.rotation = g_player.current;
	to_sprite();
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.win, img.img, 0, 0);
	return (0);
}

int		ft_key(int key,  void *args)
{
	if (key == E_KEY)
	{
		exit(EXIT_SUCCESS);
	}
	else if (key == L_KEY || key == R_KEY || key == A_KEY || key == D_KEY
	|| key == W_KEY || key == S_KEY || args)
	{
		ft_new_frame(key);
		g_player.rotation = normalize(g_player.rotation);
	}
	malloc_sprite();
	return (ft_cast_rays());
}

int		do_nothing(int key, void *args)
{
	// key = 0;
	if (key && args)
	{
	}
	return (0);
}

void	init_text(void)
{
	g_txt4.img = mlx_xpm_file_to_image(g_mlx.mlx, g_data.no_texture, &g_txt1.resolution[0], &g_txt1.resolution[1]);
	g_txt3.img = mlx_xpm_file_to_image(g_mlx.mlx, g_data.so_texture, &g_txt1.resolution[0], &g_txt1.resolution[1]);
	g_txt2.img = mlx_xpm_file_to_image(g_mlx.mlx, g_data.we_texture, &g_txt1.resolution[0], &g_txt1.resolution[1]);
	g_txt1.img = mlx_xpm_file_to_image(g_mlx.mlx, g_data.ea_texture, &g_txt1.resolution[0], &g_txt1.resolution[1]);
	g_txts.img = mlx_xpm_file_to_image(g_mlx.mlx, g_data.sp_texture, &g_txts.resolution[0], &g_txts.resolution[1]);
	if (!g_txt1.img || !g_txt2.img || !g_txt3.img || !g_txt4.img || !g_txts.img)
		ft_error("TEXTURE\n");
	g_txt1.addr = mlx_get_data_addr(g_txt1.img, &g_txt1.bits_per_pixel, &g_txt1.line_length, &g_txt1.endian);
	g_txt2.addr = mlx_get_data_addr(g_txt2.img, &g_txt2.bits_per_pixel, &g_txt2.line_length, &g_txt2.endian);
	g_txt3.addr = mlx_get_data_addr(g_txt3.img, &g_txt3.bits_per_pixel, &g_txt3.line_length, &g_txt3.endian);
	g_txt4.addr = mlx_get_data_addr(g_txt4.img, &g_txt4.bits_per_pixel, &g_txt4.line_length, &g_txt4.endian);
	g_txts.addr = mlx_get_data_addr(g_txts.img, &g_txts.bits_per_pixel, &g_txts.line_length, &g_txts.endian);
}

void	cub3d(int nb_line, int max_len)
{

	if (!(g_wall_distances = malloc(sizeof(float) * g_data.resolution[0])))
		ft_error("malloc");
	if (!(g_wall_pix = malloc(sizeof(float) * g_data.resolution[0])))
		ft_error("malloc");
	g_mlx.win = mlx_new_window(g_mlx.mlx, g_data.resolution[0], g_data.resolution[1], "CUB3D");
	draw_map(nb_line, max_len);
	img.img = mlx_new_image(g_mlx.mlx, g_data.resolution[0], g_data.resolution[1]);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_cast_rays();
	mlx_key_hook(g_mlx.win, ft_key, (void*)0);
	mlx_hook(g_mlx.win, 2, 0, ft_key, (void*)0);
	mlx_hook(g_mlx.win, 3, 0, do_nothing, (void*)0);

	// mlx_expose_hook(g_mlx.win, do_nothing, (void*)0);
	mlx_loop(g_mlx.mlx);
}
