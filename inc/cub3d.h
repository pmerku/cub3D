/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:38:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/04 14:39:23 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bpp;
	int         llen;
	int         endian;
}               t_data;

typedef struct  s_env {
	void    	*mlx;
	void    	*mlx_win;
	t_data 		data;
}               t_env;

#endif
