/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/08 15:50:36 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <cub3d.h>

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int			render_next_frame(t_win *win)
{
	for (int i = 100; i < 500; i++)
		pixel_put(&win->img, i, 100, 0x00FF0000);
	for (int i = 100; i < 500; i++)
		pixel_put(&win->img, 500, i, 0x00FF0000);
	for (int i = 500; i > 100; i--)
		pixel_put(&win->img, i, 500, 0x00FF0000);
	for (int i = 500; i > 200; i--)
		pixel_put(&win->img, 100, i, 0x00FF0000);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
