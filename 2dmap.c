/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:52:39 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/11 17:29:25 by abelarif         ###   ########.fr       */
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
			if (ft_isalpha(MAP[y][x]))
			{
				X_PLY = x * 64 + 32;
				Y_PLY = y * 64 + 32;
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
			if (MAP[(int)y / 64][(int)x / 64] == '1' || MAP[(int)y / 64][(int)x / 64] == ' ' || MAP[(int)y / 64][(int)x / 64] == '2')
			{
				X_PLY = x - 10 * xi;
				Y_PLY = y - 10 * yi;
				break;
			}
		}
		x += xi;
		y += yi;
		i++;
		X_PLY = x - xi;
		Y_PLY = y - yi;
	}
}

void	ft_move_v(int direction)
{
	get_new_position(
	X_PLY,
	Y_PLY,
	(X_PLY + (direction * -1) * cosf(A_PLY) * 100000000),
	(Y_PLY + (direction * -1) * sinf(A_PLY) * 100000000), 40);
}

void	ft_move_h(int direction)
{
	get_new_position(X_PLY,
		Y_PLY,
		(X_PLY + (direction) * cosf(A_PLY + PI / 2) * 100000000),
		(Y_PLY + (direction) * sinf(A_PLY + PI / 2) * 100000000), 18);
}

void	malloc_sprite(void)
{
	if (SP != NULL)
		free(SP);
	if (!(SP = malloc(sizeof(t_sprite) * 10000)))
		ft_error("malloc\n");
	g_nb_sprite = 0;
}

void	ft_new_frame(int key)
{
	mlx_clear_window(g_mlx.mlx, g_mlx.win);
	if (key == L_KEY)
		A_PLY = A_PLY  - PI / 40;
	if (key == R_KEY)
		A_PLY = A_PLY  + PI / 40;
	if (key == W_KEY)
		ft_move_v(-1);
	if (key == S_KEY)
		ft_move_v(1);
	if (key == A_KEY)
		ft_move_h(-1);
	if (key == D_KEY)
		ft_move_h(1);	
	if (key == L_KEY || key == R_KEY)
		A_PLY = normalize(A_PLY);
}

int		ft_cast_rays()
{
	int		step;
	float	teta;
	
	step = -1;
	teta = PI / (3 * X_RES);
	g_player.current = A_PLY;
	A_PLY = A_PLY - PI / 6;
	while (++step < X_RES)
	{
		dda(X_PLY,
		Y_PLY,
		(int)(X_PLY + cosf(A_PLY) * 100000000),
		(int)(Y_PLY + sinf(A_PLY) * 100000000), 0XFF0000, step);
		A_PLY += teta;
	}
	A_PLY = g_player.current;
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
		A_PLY = normalize(A_PLY);
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
	TXT4.img = mlx_xpm_file_to_image(g_mlx.mlx, DATA.no_texture, &TXT1.resolution[0], &TXT1.resolution[1]);
	TXT3.img = mlx_xpm_file_to_image(g_mlx.mlx, DATA.so_texture, &TXT1.resolution[0], &TXT1.resolution[1]);
	TXT2.img = mlx_xpm_file_to_image(g_mlx.mlx, DATA.we_texture, &TXT1.resolution[0], &TXT1.resolution[1]);
	TXT1.img = mlx_xpm_file_to_image(g_mlx.mlx, DATA.ea_texture, &TXT1.resolution[0], &TXT1.resolution[1]);
	TXTS.img = mlx_xpm_file_to_image(g_mlx.mlx, DATA.sp_texture, &TXTS.resolution[0], &TXTS.resolution[1]);
	if (!TXT1.img || !TXT2.img || !TXT3.img || !TXT4.img || !TXTS.img)
		ft_error("TEXTURE\n");
	TXT1.addr = mlx_get_data_addr(TXT1.img, &TXT1.bits_per_pixel, &TXT1.line_length, &TXT1.endian);
	TXT2.addr = mlx_get_data_addr(TXT2.img, &TXT2.bits_per_pixel, &TXT2.line_length, &TXT2.endian);
	TXT3.addr = mlx_get_data_addr(TXT3.img, &TXT3.bits_per_pixel, &TXT3.line_length, &TXT3.endian);
	TXT4.addr = mlx_get_data_addr(TXT4.img, &TXT4.bits_per_pixel, &TXT4.line_length, &TXT4.endian);
	TXTS.addr = mlx_get_data_addr(TXTS.img, &TXTS.bits_per_pixel, &TXTS.line_length, &TXTS.endian);
}

void	cub3d(int nb_line, int max_len)
{

	if (!(g_wall_distances = malloc(sizeof(float) * X_RES)))
		ft_error("malloc");
	if (!(g_wall_pix = malloc(sizeof(float) * X_RES)))
		ft_error("malloc");
	g_mlx.win = mlx_new_window(g_mlx.mlx, X_RES, Y_RES, "CUB3D");
	draw_map(nb_line, max_len);
	img.img = mlx_new_image(g_mlx.mlx, X_RES, Y_RES);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	malloc_sprite();
	ft_cast_rays();
	mlx_key_hook(g_mlx.win, ft_key, (void*)0);
	mlx_hook(g_mlx.win, 2, 1L << 0, ft_key, (void*)0);
	mlx_hook(g_mlx.win, 3, 0, do_nothing, (void*)0);

	mlx_expose_hook(g_mlx.win, do_nothing, (void*)0);
	mlx_loop(g_mlx.mlx);
}
