/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:04:54 by abelarif          #+#    #+#             */
/*   Updated: 2020/11/29 04:15:20 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		bad_char(const char *line, int i)
{
	if (!(line[i] == '1' || line[i] == '0' || line[i] == '2'
	|| line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
	|| line[i] == 'W' || line[i] == ' ' || line[i] == '\t'))
		ft_error("BAAAD CHAR\n");
}

void		check_horizontal(int x, int y, int y_max)
{
	if (y == 0)
		ft_error("bad char at first line\n");
	else if (y == y_max - 1)
		ft_error("bad char at last line\n");
	else if (g_map[y - 1][x] != '0' && g_map[y - 1][x] != '1'
	&& g_map[y - 1][x] != '2' && g_map[y - 1][x] != 'N'
	&& g_map[y - 1][x] != 'E' && g_map[y - 1][x] != 'S'
	&& g_map[y - 1][x] != 'W')
		ft_error("+++++++++++++++++++++");
	else if (g_map[y + 1][x] != '0' && g_map[y + 1][x] != '1'
	&& g_map[y + 1][x] != '2' && g_map[y + 1][x] != 'N'
	&& g_map[y + 1][x] != 'E' && g_map[y + 1][x] != 'S'
	&& g_map[y + 1][x] != 'W')
		ft_error("---------------------0");
}

void		get_player(char orientation, int x, int y)
{
	if (g_player.rotation)
		ft_error("Multiple definition of Player\n");
	g_player.x = x;
	g_player.y = y;
	if (orientation == 'N')
		g_player.rotation = - (PI / 2);
	else if (orientation == 'S')
		g_player.rotation = PI / 2;
	else if (orientation == 'E')
		g_player.rotation = 0;
	else if (orientation == 'W')
		g_player.rotation = PI;
}

void		bef_aft(char check_char, const char *line, int nb_line, int i)
{
	if (check_char == 'N' || check_char == 'S'
	|| check_char == 'E' || check_char == 'W')
		get_player(check_char, i, nb_line);
	if (i == 0 || i == (int)ft_strlen(line) - 1)
		ft_error("First or Last char in map\n");
	else if (line[i - 1] == ' ' || line[i - 1] == '\t')
		ft_error("BEFORE\n");
	else if (line[i + 1]
	&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		ft_error("AFTER\n");
}

void		check_line(const char *line, int nb_line)
{
	int				i;
	int				j;
	const char		*check_char = "02NSEW";

	i = -1;
	while (line[++i])
	{
		j = -1;
		while (check_char[++j])
		{
			bad_char(line, i);
			if (check_char[j] == line[i])
			{
				bef_aft(check_char[j], line, nb_line, i);
			}
		}
	}
}

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
	}
	if (r == 0)
		ft_error("No Map\n");
	return (0);
}

void		horizontal_map(int y_max)
{
	int		y;
	int		i;
	int		x;
	char	*check_char;

	y = -1;
	check_char = "02ENSW";
	while (g_map[++y])
	{
		x = -1;
		while (g_map[y][++x])
		{
			i = -1;
			while (check_char[++i])
			{
				if (check_char[i] == g_map[y][x])
					check_horizontal(x, y, y_max);
			}
		}
	}
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
	while (nb_line >= 0 && g_map[nb_line])
	{
		my_strlcpy(g_map[nb_line], actual->line, ft_strlen(actual->line));
		if ((i = ft_strlen(actual->line)) < max_len)
		{
			if (i == 0 && nb_line > 0)
				ft_error("egntnrtyn");
			while (i < max_len)
			{
				g_map[nb_line][i] = ' ';
				i++;
			}
			g_map[nb_line][i] = '\0';
		}
		actual = actual->next;
		nb_line--;
	}
}

void		map_2d(int nb_line, int max_len)
{
	int		i;

	i = 0;
	if ((g_map = malloc(sizeof(char *) * (nb_line + 1))) == 0)
		ft_error("malloc map 1\n");
	g_map[nb_line] = NULL;
	while (i < nb_line)
	{
		if ((g_map[i] = malloc(sizeof(char) * (max_len + 1))) == 0)
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
