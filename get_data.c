/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:40:48 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/09 16:50:26 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_resolution(char **content)
{
	if (ft_strlen(content[0]) != 1)
		ft_error("Resolution00\n");
	if (ft_strncmp("R", content[0], 1))
		ft_error("Resolution01\n");
	if (all_digit(content[1]) && all_digit(content[2]) && g_data.nb[0] == 0)
	{
		g_data.nb[0] = 1;
		X_RES = ft_atoi(content[1]);
		Y_RES = ft_atoi(content[2]);
		return (1);
	}
	else if (g_data.nb[0] == 1)
	{
		ft_error("Resolution already exist\n");
		return (1);
	}
	else
		ft_error("Resolution value\n");
	return (0);
}

void	get_cl(int r, int g, int b)
{
	g_data.ce_color[0] = r;
	g_data.ce_color[1] = g;
	g_data.ce_color[2] = b;
}

void	get_fl(int r, int g, int b)
{
	g_data.fl_color[0] = r;
	g_data.fl_color[1] = g;
	g_data.fl_color[2] = b;
}

int		get_rgb(int index, const char *str)
{
	char	**rgb;
	int		nb;

	nb = 0;
	rgb = ft_split(str, ',');
	while (rgb[nb])
		nb++;
	if (nb != 3)
		ft_error("RGB\n");
	if (!(all_digit(rgb[0]) && all_digit(rgb[1]) && all_digit(rgb[2])))
		ft_error("RGB\n");
	if (index == 6)
		get_cl(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else
		get_fl(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	g_data.nb[index] = 1;
	nb = -1;
	while (++nb <= 3)
		free(rgb[nb]);
	free(rgb);
	return (1);
}

int		get_path(int index, const char *str)
{
	if (g_data.nb[index] != 0)
		ft_error("Texture\n");
	else if (index == 1 && g_data.nb[1] == 0)
		g_data.no_texture = ft_strdup(str);
	else if (index == 2 && g_data.nb[2] == 0)
		g_data.so_texture = ft_strdup(str);
	else if (index == 3 && g_data.nb[3] == 0)
		g_data.we_texture = ft_strdup(str);
	else if (index == 4 && g_data.nb[4] == 0)
		g_data.ea_texture = ft_strdup(str);
	else if (index == 5 && g_data.nb[5] == 0)
		g_data.sp_texture = ft_strdup(str);
	else if (index == 6 && g_data.nb[6] == 0)
		return (get_rgb(index, str));
	else if (index == 7 && g_data.nb[7] == 0)
		return (get_rgb(index, str));
	else
		ft_error("Texture exist\n");
	g_data.nb[index] = 1;
	return (1);
}
