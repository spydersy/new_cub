/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:04:54 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 09:41:55 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			skip_void(int fd)
{
	char		*line;
	int			r;

	r = 1;
	while ((r = get_next_line(fd, &line)))
	{
		if (skip_line(line) == 0)
		{
			check_line(line, 1);
			g_liste = initialisation(line);
			r = ft_strlen(line);
			return (r);
		}
		free(line);
	}
	if (r == 0)
		ft_error("No Map\n");
	return (0);
}

size_t		my_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t size_src;

	i = 0;
	if (!src)
		return (0);
	size_src = ft_strlen(src);
	if (size > 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	return (size_src);
}

void		ft_move(int nb_line, int max_len)
{
	t_line		*actual;
	int			i;

	actual = g_liste->first;
	nb_line--;
	while (nb_line >= 0 && MAP[nb_line])
	{
		my_strlcpy(MAP[nb_line], actual->line, ft_strlen(actual->line));
		if ((i = ft_strlen(actual->line)) < max_len)
		{
			if (i == 0 && nb_line > 0)
				ft_error("egntnrtyn");
			while (i < max_len)
			{
				MAP[nb_line][i] = ' ';
				i++;
			}
			MAP[nb_line][i] = '\0';
		}
		actual = actual->next;
		nb_line--;
	}
}

void		map_2d(int nb_line, int max_len)
{
	int		i;

	i = 0;
	if ((MAP = malloc(sizeof(char *) * (nb_line + 1))) == 0)
		ft_error("malloc map 1\n");
	MAP[nb_line] = NULL;
	while (i < nb_line)
	{
		if ((MAP[i] = malloc(sizeof(char) * (max_len + 1))) == 0)
			ft_error("malloc map 2\n");
		i++;
	}
	ft_move(nb_line, max_len);
	horizontal_map(nb_line);
	cub3d(nb_line, max_len);
}

void		ft_map(int fd)
{
	int				r;
	char			*line;

	r = 1;
	nb_line = 0;
	max_len = skip_void(fd);
	nb_line++;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		nb_line++;
		insertion(g_liste, line);
		max_len = (max_len < (int)ft_strlen(line)
		? ((int)ft_strlen(line)) : (max_len));
		if (skip_line(line) == 0)
			check_line(line, max_len);
	}
	nb_line++;
	check_line(line, nb_line);
	insertion(g_liste, line);
	map_2d(nb_line, max_len);
}
