/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 15:22:02 by prmerku          ###   ########.fr       */
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
#include <mach/notify.h>

/*
** ---------------------------------------------------------------------------
** 							Macro defines
** ---------------------------------------------------------------------------
*/

# define BMP_FILE	"frame.bmp"
# define BMP_BPP	3
# define BMP_HSIZE	14
# define BMP_ISIZE	40

# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_UP		126
# define KEY_LEFT	123
# define KEY_DOWN	125
# define KEY_RIGHT	124
# define KEY_ESC	53

# define MOV_SPEED	0.0575
# define ROT_SPEED	0.0275

# define N_WALL		0
# define S_WALL		1
# define W_WALL		2
# define E_WALL		3
# define FLOOR		4
# define CEILING	5
# define DOOR		6

# define SPR_T1		7	//sprite tex
# define SPR_T2		8
# define SPR_T3		9
# define SPR_I		10	//item
# define SPR_C		11	//collectible
# define SPR_TR		12	//trap
# define SPR_M		13	//monster

# define S_NUM		7
# define T_NUM		14

# define CHAR_SET	"01234NSEWHDMICT"
# define SPAWN_SET	"NSEW"
# define SPRITE_SET	"234MICT"
# define EXTRA_SET	"HD" // H = hidden, D = door

/*
** ---------------------------------------------------------------------------
** 							Cub3D Structs
** ---------------------------------------------------------------------------
*/

/*
** Keys struct
*/

typedef struct	s_key {
	u_int		up:1;
	u_int		left:1;
	u_int		down:1;
	u_int		right:1;
	u_int		rot_l:1;
	u_int		rot_r:1;
}				t_key;
/*
** Movement struct
*/

typedef struct	s_mov {
	double		perp_wd;
	int			step_x;
	int			step_y;
	u_int		hit:1;
	u_int		side:1;
	double		m_speed;
	double		r_speed;
	float		step_fx;
	float		step_fy;
	int			cell_x;
	int			cell_y;
}				t_mov;

/*
** Player position struct
*/

typedef struct	s_pos {
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	float		rwd;
	double		tmp_x;
	double		tmp_y;
}				t_pos;

/*
** Raycaster struct
*/

typedef struct	s_ray {
	double		dir_x;
	double		dir_y;
	float		dir_x0;
	float		dir_y0;
	float		dir_x1;
	float		dir_y1;
	float		fx;
	float		fy;
	double		side_dx;
	double		side_dy;
	double		delta_dx;
	double		delta_dy;
	int			draw_s;
	int			draw_e;
	double		wall_x;
}				t_ray;

/*
** Image struct
*/

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			line_h;
}				t_img;

/*
** Map struct
*/

typedef struct	s_map {
	char		**map;
	int			x;
	int			y;
	int			map_h;
	int			map_w;
}				t_map;

/*
** Color struct
*/

typedef struct	s_color {
	u_int		a;
	u_int		r;
	u_int		g;
	u_int		b;
	u_int		f_color;
	u_int		c_color;
	u_int 		bmp_color;
	int			tex_i;
	int 		spr_i;
}				t_color;

typedef struct	s_typ {
	char		c;
	int			tex_i;
}				t_typ;

/*
** Sprites struct
*/

typedef struct	s_sdt {
	double		spr_x;
	double		spr_y;
	double		inv_d;
	double		trs_x;
	double		trs_y;
	int 		spr_sx;
	int 		spr_d;
	int			draw_sy;
	int			draw_ey;
	int			draw_sx;
	int			draw_ex;
	int			d;
}				t_sdt;

typedef struct	s_spr {
	double		x;
	double		y;
	int 		tex_id;
	double		dist;
}				t_spr;

/*
** Textures struct
*/

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

/*
** Window struct / main struct
*/

typedef struct	s_win {
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;
	int			save:1;
	t_img		img[2];
	u_int		i:1;
	t_pos		pos;
	t_ray		ray;
	t_map		map;
	t_color		color;
	t_tex		tex[T_NUM];
	t_typ		type[S_NUM];
	double		*z_buff;
	t_sdt		sdt;
	t_spr		*spr;
	int			spr_i;
	t_mov		mov;
	t_key		key;
}				t_win;

/*
** ---------------------------------------------------------------------------
** 							Cub3D functions
** ---------------------------------------------------------------------------
*/

#endif
