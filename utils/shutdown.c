/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:27:38 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 10:11:45 by prmerku          ###   ########.fr       */
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
	mlx_destroy_image(win->mlx, win->mlx_win);
	exit(EXIT_SUCCESS);
}

/*
** Clean exit program on correct keycode
**
** @param  char * error string to be printed
** @exit   int    status code 0
** @return int    status code
*/

int		close_key(int keycode, t_win *win)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(win->mlx, win->mlx_win);
		exit(EXIT_SUCCESS);
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
