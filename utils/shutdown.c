/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:27:38 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 09:43:46 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_unistd.h>
#include <ft_string.h>
#include <mlx.h>
#include "cub3d.h"

/*
** Clean exit program on ESC key press
**
** @param  t_win *win allocated global window structure
** @return int        status code
*/

int			close_key(t_win *win)
{
	int		i;

	if (win->mlx && win->mlx_win)
	{
		i = 0;
		while (i < T_NUM)
		{
			if (win->tex[i].wall)
				mlx_destroy_image(win->mlx, win->tex[i].wall);
			i++;
		}
		if (win->img[0].img)
			mlx_destroy_image(win->mlx, win->img[0].img);
		if (win->img[1].img)
			mlx_destroy_image(win->mlx, win->img[1].img);
		if (!win->save)
			mlx_destroy_window(win->mlx, win->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/*
** Clean exit program
**
** @param  t_win *win allocated global window structure
** @return int        status code
*/

int			close_win(t_win *win)
{
	int		i;

	if (!win->mlx)
		return (0);
	i = 0;
	while (i < T_NUM)
	{
		if (win->tex[i].wall)
			mlx_destroy_image(win->mlx, win->tex[i].wall);
		i++;
	}
	if (win->img[0].img)
		mlx_destroy_image(win->mlx, win->img[0].img);
	if (win->img[1].img)
		mlx_destroy_image(win->mlx, win->img[1].img);
	exit(EXIT_SUCCESS);
}

/*
** Print error message
**
** @param char * error string to be printed
** @exit  int    status code 1
*/

int			close_error(char *s)
{
	ft_write(1, "Error\n", 6);
	ft_write(1, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
