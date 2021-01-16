/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 09:36:05 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/16 09:40:16 by abelarif         ###   ########.fr       */
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
	else if (MAP[y - 1][x] != '0' && MAP[y - 1][x] != '1'
	&& MAP[y - 1][x] != '2' && MAP[y - 1][x] != 'N'
	&& MAP[y - 1][x] != 'E' && MAP[y - 1][x] != 'S'
	&& MAP[y - 1][x] != 'W')
		ft_error("+++++++++++++++++++++");
	else if (MAP[y + 1][x] != '0' && MAP[y + 1][x] != '1'
	&& MAP[y + 1][x] != '2' && MAP[y + 1][x] != 'N'
	&& MAP[y + 1][x] != 'E' && MAP[y + 1][x] != 'S'
	&& MAP[y + 1][x] != 'W')
		ft_error("---------------------0");
}

void		horizontal_map(int y_max)
{
	int		y;
	int		i;
	int		x;
	char	*check_char;

	y = -1;
	check_char = "02ENSW";
	while (MAP[++y])
	{
		x = -1;
		while (MAP[y][++x])
		{
			i = -1;
			while (check_char[++i])
			{
				if (check_char[i] == MAP[y][x])
					check_horizontal(x, y, y_max);
				if (MAP[y][x] == '2')
					g_nb_sprite++;
			}
		}
	}
}

void		bef_aft(char check_char, const char *line, int nb_line, int i)
{
	if (check_char == 'N' || check_char == 'S'
	|| check_char == 'E' || check_char == 'W')
		get_player_angle(check_char, i, nb_line);
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
