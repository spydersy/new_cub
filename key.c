/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 10:03:00 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/19 08:49:48 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_move_v(int direction)
{
	get_new_position(
	(X_PLY + (direction * -1) * cosf(A_PLY) * 100000000),
	(Y_PLY + (direction * -1) * sinf(A_PLY) * 100000000), 60);
}

void		ft_move_h(int direction)
{
	get_new_position(
	(X_PLY + (direction) * cosf(A_PLY + PI / 2) * 100000000),
	(Y_PLY + (direction) * sinf(A_PLY + PI / 2) * 100000000), 18);
}

void		ft_new_frame(int key)
{
	mlx_clear_window(g_mlx.mlx, g_mlx.win);
	if (key == L_KEY)
		A_PLY = A_PLY - PI / 40;
	if (key == R_KEY)
		A_PLY = A_PLY + PI / 40;
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

int			ft_key(int key, void *args)
{
	printf("key : %d\n", key);
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
