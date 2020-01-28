/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/28 10:42:01 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ---------------------------------------------------------------------------
** 							Header includes
** ---------------------------------------------------------------------------
*/

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>


#include <stdio.h>

/*
** ---------------------------------------------------------------------------
** 							Macro defines
** ---------------------------------------------------------------------------
*/

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_UP		126
# define KEY_LEFT	123
# define KEY_DOWN	125
# define KEY_RIGHT	124
# define KEY_Q		12
# define KEY_E		14
# define KEY_ESC	53

/*
** ---------------------------------------------------------------------------
** 							Cub3D Structs
** ---------------------------------------------------------------------------
*/

typedef struct	s_key
{
	unsigned int	up:1;
	unsigned int	left:1;
	unsigned int	down:1;
	unsigned int	right:1;
	unsigned int	rot_l:1;
	unsigned int	rot_r:1;
}				t_key;

typedef struct	s_mov
{
	double			perp_wd;
	int				step_x;
	int				step_y;
	unsigned int	hit:1;
	unsigned int	side:1;
	double			m_speed;
	double			r_speed;
}				t_mov;

typedef struct	s_pos
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
}				t_pos;

typedef struct	s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dx;
	double		side_dy;
	double		delta_dx;
	double		delta_dy;
	int			draw_s;
	int			draw_e;
}				t_ray;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			line_h;
}				t_img;

typedef struct	s_map
{
	char		**map;
	int			x;
	int			y;
	int			map_h;
	int			map_w;
	char		*sprite;
}				t_map;

typedef struct	s_color
{
	unsigned int	a:8;
	unsigned int	r:8;
	unsigned int	g:8;
	unsigned int	b:8;
	unsigned int	f_color;
	unsigned int	c_color;
	unsigned int	tex_n;
	u_int		tex_c;
}				t_color;

typedef struct	s_tex
{
	void		*wall;
	char 		*data;
	int			tex_w;
	int			tex_h;
	int			bpp;
	int			line_len;
	int			endian;
}				t_tex;

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
	t_color		color;
	t_tex		tex[5];
	t_mov		mov;
	t_key		key;
}				t_win;

/*
** ---------------------------------------------------------------------------
** 							Cub3D functions
** ---------------------------------------------------------------------------
*/

#endif
