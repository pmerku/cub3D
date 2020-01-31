/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/30 14:55:22 by prmerku          ###   ########.fr       */
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
# define KEY_ESC	53

# define N_WALL	0
# define S_WALL	1
# define W_WALL	2
# define E_WALL	3

# define CHAR_SET	"0123NSEW"
# define SPAWN_SET	"NSEW"

/*
** ---------------------------------------------------------------------------
** 							Cub3D Structs
** ---------------------------------------------------------------------------
*/

typedef struct	s_key {
	u_int		up:1;
	u_int		left:1;
	u_int		down:1;
	u_int		right:1;
	u_int		rot_l:1;
	u_int		rot_r:1;
}				t_key;

typedef struct	s_mov {
	double		perp_wd;
	int			step_x;
	int			step_y;
	u_int		hit:1;
	u_int		side:1;
	double		m_speed;
	double		r_speed;
}				t_mov;

typedef struct	s_pos {
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
}				t_pos;

typedef struct	s_ray {
	double		dir_x;
	double		dir_y;
	double		side_dx;
	double		side_dy;
	double		delta_dx;
	double		delta_dy;
	int			draw_s;
	int			draw_e;
	double		wall_x;
}				t_ray;

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			line_h;
}				t_img;

typedef struct	s_map {
	char		**map;
	int			x;
	int			y;
	int			map_h;
	int			map_w;
	char		*sprite;
}				t_map;

typedef struct	s_color {
	u_int		a;
	u_int		r;
	u_int		g;
	u_int		b;
	u_int		f_color;
	u_int		c_color;
	int			tex_i;
}				t_color;

typedef struct	s_tex {
	void		*wall;
	char		*data;
	int			tex_w;
	int			tex_h;
	int			bpp;
	int			line_len;
	int			endian;
	u_int		tex_x;
	u_int		tex_y;
}				t_tex;

typedef struct	s_win {
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;
	t_img		img[2];
	u_int		i:1;
	t_pos		pos;
	t_ray		ray;
	t_map		map;
	t_color		color;
	t_tex		tex[4];
	t_mov		mov;
	t_key		key;
}				t_win;

/*
** ---------------------------------------------------------------------------
** 							Cub3D functions
** ---------------------------------------------------------------------------
*/

#endif
