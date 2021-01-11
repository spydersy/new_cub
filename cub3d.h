/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:14:32 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/09 16:13:19 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CUB3D_H
#	define CUB3D_H

#	include <unistd.h>
#	include <string.h>
#	include <stdlib.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <stdio.h>
#	include <math.h>
#	include "./link.h"
#	include "./GNL/get_next_line.h"
#	include "./LBFT/libft.h"


#define PI 3.14159265359

// #define A_KEY	97
// #define D_KEY	100
// #define W_KEY	119
// #define S_KEY	115
// #define L_KEY	65361
// #define R_KEY	65363
// #define E_KEY	65307
// #include "../mlx.h"

#define A_KEY	0
#define D_KEY	2
#define W_KEY	13
#define S_KEY	1
#define L_KEY	123
#define R_KEY	124
#define E_KEY	53
#include <mlx.h>

#define X_RES	g_data.resolution[0]
#define Y_RES	g_data.resolution[1]

typedef struct	s_data
{
	int			resolution[2];
	int			nb[8];
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*sp_texture;
	int			ce_color[3];
	int			fl_color[3];
	int			save;
}				t_data;

typedef	struct	s_player
{
	float			x;
	float			y;
	float			current;
	float			rotation;
	int				col;
}				t_player;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*nmlx;
	void		*nwin;

}				t_mlx;

typedef struct  s_img
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			resolution[2];
}               t_img;


typedef struct	s_sprite
{
	int		x_map;
	int		y_map;

	float	x;
	float	y;

	float	distance;

	float	angle;
	float	size;
	float	xof;
	float	yof;

	int		index;
}				t_sprite;



char			**g_map;
t_player		g_player;
t_data			g_data;
t_liste			*g_liste;
t_mlx			g_mlx;
t_img			img;

t_img			g_txt1;
t_img			g_txt2;
t_img			g_txt3;
t_img			g_txt4;
t_img			g_txts;

t_sprite		*g_sp;

int				nb_line;
int				max_len;

float				dist;
int					g_nb_sprite;

float					*g_wall_distances;
float					*g_wall_pix;

void				init_text(void);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
float				distance(float x0, float y0, float x1, float y1);
float				vabs(float i);
void                ft_error (char *str);
void				dda(float x0, float y0,  float x1, float y1, int color, int col);
int                 max_of(int i, int j);
int                 min_of(int i, int j);
void                ft_data(int fd);
void        		ft_map(int fd);
int					skip_line(const char *line);
int					get_resolution(char **content);
void				get_cl(int r, int g, int b);
void				get_fl(int r, int g, int b);
int					get_rgb(int index, const char *str);
int					get_path(int index, const char *str);
void				ft_init(void);
int					all_digit(const char *str);
int					skip_line(const char *line);
int					manip_line(const char *line);
int					get_texture(char **content);
void				cub3d(int nb_line, int max_len);
int					sprite(float x, float y);
int					check_sprite(float x, float y);
void				to_sprite(void);
#endif
