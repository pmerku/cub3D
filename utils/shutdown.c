/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:27:38 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 14:50:33 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <cub3d.h>

/*
** Clean exit program on window close button press
**
** @param  t_win *win allocated global window structure
** @exit   int        status code 0
** @return int        status code
*/

int		close_win(t_win *win)
{
	int 	i;

	if (win->mlx && win->mlx_win)
	{
		i = 0;
		while (win->tex[i].wall)
			mlx_destroy_image(win->mlx, win->tex[i].wall);
		mlx_destroy_image(win->mlx, win->img[0].img);
		mlx_destroy_image(win->mlx, win->img[1].img);
		mlx_destroy_window(win->mlx, win->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

/*
** Clean exit program on correct keycode
**
** @param  t_win    *win allocated global window structure
** @param  int   keycode pressed key id
** @exit   int    status code 0
** @return int    status code
*/

int		close_key(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
	{
		if (win->mlx && win->mlx_win)
		{
			mlx_destroy_image(win->mlx, win->img[0].img);
			mlx_destroy_image(win->mlx, win->img[1].img);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

/*
** Print error message
**
** @param char * error string to be printed
** @exit  int    status code 1
*/

int		close_error(char *s)
{
	write(1, "Error\n", 6);
	write(1, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
