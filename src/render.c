/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/10 14:07:42 by prmerku          ###   ########.fr       */
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
	for(int x = 0; x < win->win_x; x++)
	win->pos.pos_x = 22;
	win->pos.pos_y = 12;
	win->pos.dir_x = -1;
	win->pos.dir_y = 0;
	win->pos.plane_x = 0;
	win->pos.plane_y = 0.66;


	//pixel_put(&win->img, 100, i, 0x00FF0000);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
