/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 08:54:53 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/19 10:01:43 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    	color_converter(int hex)
{

	g_data.ce_color[0] = ((hex >> 16) & 0xFF);
	g_data.ce_color[1] = ((hex >> 8) & 0xFF);
	g_data.ce_color[2] = ((hex) & 0xFF);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char *s;

	d = dst;
	s = src;
	if (d == 0 && s == 0)
		return (0);
	while (n--)
		*d++ = *s++;
	return (dst);
}

void    	init_bmp_info(void)
{
	int i;

	i = -1;
	g_bmp.bitcount = 24;
	g_bmp.width_in_bytes = ((X_RES * g_bmp.bitcount + 31) / 32) * 4;
	g_bmp.imagesize = g_bmp.width_in_bytes * Y_RES;
	g_bmp.bi_size = 40;
	g_bmp.bf_off_bits = 54;
	g_bmp.filesize = 54 + g_bmp.imagesize;
	g_bmp.bi_planes = 1;
	while (++i < 54)
		g_bmp.header[i] = 0;
}

void	init_header(void)
{
	ft_memcpy(g_bmp.header, "BM", 2);
	ft_memcpy(g_bmp.header + 2,  &g_bmp.filesize, 4);
	ft_memcpy(g_bmp.header + 10, &g_bmp.bf_off_bits, 4);
	ft_memcpy(g_bmp.header + 14, &g_bmp.bi_size, 4);
	ft_memcpy(g_bmp.header + 18, &X_RES, 4);
	ft_memcpy(g_bmp.header + 22, &Y_RES, 4);
	ft_memcpy(g_bmp.header + 26, &g_bmp.bi_planes, 2);
	ft_memcpy(g_bmp.header + 28, &g_bmp.bitcount, 2);
	ft_memcpy(g_bmp.header + 34, &g_bmp.imagesize, 4);
	g_bmp.buf = malloc(g_bmp.imagesize);
}

void	fill_the_buffer(void)
{
	int		row;
	int		col;

	row = -1;
	while (++row < Y_RES)
	{
		col = -1;
		while (++col < X_RES)
		{
            // color_converter(((unsigned char*)img.img)[row * Y_RES + col]);
            // color_converter(0xffffff);
			g_bmp.buf[(Y_RES - 1 - row)
			* g_bmp.width_in_bytes + col * 3 + 0] = 0xff;
			g_bmp.buf[(Y_RES - 1 - row)
			* g_bmp.width_in_bytes + col * 3 + 1] = 0xff;
			g_bmp.buf[(Y_RES - 1 - row)
			* g_bmp.width_in_bytes + col * 3 + 2] = 0xff;
		}
	}
}

void        ft_save(void)
{
	int				fd;

	// get_position(nb_line, max_len);
	// img.img = mlx_new_image(g_mlx.mlx, X_RES, Y_RES);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	// malloc_sprite();
	// ft_cast_rays();
    
	init_bmp_info();
	init_header();
	fill_the_buffer();
    fd = open("screen_shot.bmp", O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0x777);
	write(fd, g_bmp.header, 54);
	write(fd, (char*)g_bmp.buf, g_bmp.imagesize);
    close(fd);
    exit(EXIT_SUCCESS);
}