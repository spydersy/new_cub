/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:37:18 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/09 16:16:47 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(void)
{
	g_data.nb[0] = 0;
	g_data.nb[1] = 0;
	g_data.nb[2] = 0;
	g_data.nb[3] = 0;
	g_data.nb[4] = 0;
	g_data.nb[5] = 0;
	g_data.nb[6] = 0;
	g_data.nb[7] = 0;
	X_RES = -1;
	Y_RES = -1;
	g_player.x = -1;
	g_player.y = -1;
	g_player.rotation = 0;
	g_txt1.resolution[0] = 128;
	g_txt1.resolution[1] = 124;
	g_txts.resolution[0] = 64;
	g_txts.resolution[1] = 64;
}

int		all_digit(const char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

int		skip_line(const char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	free_array(char **array)
{
	int		i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
}

int		manip_line(const char *line)
{
	char			**content;
	static int		nb_data = 0;
	int				nb;

	nb = 0;
	if ((content = ft_split(line, ' ')) == NULL)
		ft_error("Split\n");
	if (!ft_isalpha(line[0]))
		ft_error("FIRST CHAR\n");
	while (content[nb])
		nb++;
	if (nb == 3)
	{
		nb_data += get_resolution(content);
		free_array(content);
	}
	else if (nb == 2)
	{
		nb_data += get_texture(content);
		free_array(content);
	}
	else
		ft_error("Content line\n");
	return (1);
}
