/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:27:38 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/10 09:41:58 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>

int		close_key(int keycode, t_win *win)
{
	if (keycode == 53)
	{
		mlx_destroy_window(win->mlx, win->mlx_win);
		exit(0);
	}
	return (0);
}

int		close_error(int i)
{
	write(1, "Error\n", 6);
	if (i == 0)
		write(1, "Invalid file\n", 13);
	else if (i == 1)
		write(1, "No such file or can't open file\n", 32);
	else
		write(1, "Error\n", 6);
	exit(1);
}
