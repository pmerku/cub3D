/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/08 17:28:12 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct	s_pos {
	int 	pos_x;
	int 	pos_y;
}				t_pos;

typedef struct  s_img {
	void        *img;
	char        *addr;
	int         bpp;
	int         llen;
	int         endian;
	int 		img_x;
	int 		img_y;
}               t_img;

typedef struct  s_win {
	void    	*mlx;
	void    	*mlx_win;
	int 		win_x;
	int 		win_y;
	char 		**map;
	t_img 		img;
	t_pos		pos;
}               t_win;

int		render_next_frame(t_win *win);

void	parse_file(char *s, t_win *win);
void	parse_resolution(char *buf, t_win *win);

int		close_key(int keycode, t_win *win);
int		close_error(int i);

#endif
