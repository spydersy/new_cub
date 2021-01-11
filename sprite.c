/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:15:08 by abelarif          #+#    #+#             */
/*   Updated: 2020/12/21 10:16:34 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(float x, float y)
{
	g_sp[g_nb_sprite].x_map = x / 64;
	g_sp[g_nb_sprite].y_map = y / 64;
	g_sp[g_nb_sprite].index = -1;
	g_sp[g_nb_sprite].x = g_sp[g_nb_sprite].x_map * 64 + 32;
	g_sp[g_nb_sprite].y = g_sp[g_nb_sprite].y_map * 64 + 32;

	g_sp[g_nb_sprite].distance = distance(g_player.x, g_player.y,
	g_sp[g_nb_sprite].x , g_sp[g_nb_sprite].y);
	
	g_sp[g_nb_sprite].distance = g_sp[g_nb_sprite].distance
	* cos(vabs(g_player.current - g_player.rotation));
	
	g_nb_sprite++;
}

int		check_sprite(float x, float y)
{
	int		x_position;
	int		y_position;
	int		i;

	x_position = x / 64;
	y_position = y / 64;
	i = -1;

	if (g_nb_sprite == 0)
	{

		add_sprite(x, y);
		return (0);
	}
	while (++i < g_nb_sprite)
	{
		if (x_position ==  g_sp[i].x_map && y_position == g_sp[i].y_map)
		{
			return (0);
		}
	}
	add_sprite(x, y);
	return (0);
}