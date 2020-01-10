/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/10 12:06:01 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct	s_pos
{
	int 	pos_x;
	int 	pos_y;
}				t_pos;

typedef struct  s_img
{
	void        *img;
	char        *addr;
	int         bpp;
	int         llen;
	int         endian;
}               t_img;

typedef struct	s_map
{
	char		**map;
	int 		map_x;
	int 		map_y;
	char 		*sprite;
}				t_map;

typedef struct	s_tex
{
	int 		t;
	int 		r;
	int 		g;
	int 		b;
	int			f_color;
	int 		c_color;
}				t_tex;

typedef struct  s_win
{
	void    	*mlx;
	void    	*mlx_win;
	int 		win_x;
	int 		win_y;
	t_img 		img;
	t_pos		pos;
	t_map 		map;
	t_tex 		tex;
}               t_win;

int		render_next_frame(t_win *win);

void	parse_file(char *s, t_win *win);
void	parse_resolution(char **data, t_win *win, int *i);
void	parse_sprite(void);
void	parse_texture(char **data, t_win *win, int *i);

void	delete_data(char **data);
int		close_key(int keycode, t_win *win);
int		close_error(int i);

#endif
