/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/13 16:07:16 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_pos
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		camera_y;
}				t_pos;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int 		line_h;
}				t_img;

typedef struct	s_map
{
	char		**map;
	int			x;
	int			y;
	int 		map_l;
	int 		map_h;
	char		*sprite;
}				t_map;

typedef struct	s_tex
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	int				f_color;
	int				c_color;
}				t_tex;

typedef struct	s_mov
{
	double		perp_wd;
	int			step_x;
	int			step_y;
	int 		hit;
	int 		side;
}				t_mov;

typedef struct	s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dx;
	double		side_dy;
	double		delta_dx;
	double		delta_dy;
}				t_ray;

typedef struct	s_win
{
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;
	t_img		img;
	t_pos		pos;
	t_ray		ray;
	t_map		map;
	t_tex		tex;
	t_mov		mov;
}				t_win;

int				render_next_frame(t_win *win);

void			parse_file(char *s, t_win *win);
void			parse_resolution(char **data, t_win *win, int *i);
void			parse_sprite(void);
void			parse_texture(char **data, t_win *win, int *i);

void			delete_data(char **data);
int				close_key(int keycode, t_win *win);
int				close_error(int i);

#endif
