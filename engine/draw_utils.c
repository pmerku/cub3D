/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/05 14:52:20 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// TODO: maybe redo the map checking (add offset/hit box)

int		query_map(t_win *win, double y, double x)
{
	if (y < 0 || y >= win->map.map_h || x < 0 || x >= win->map.map_w
		|| win->map.map[(int)y][(int)x] == '1')
	{
		if (win->map.map[(int)floor(y)][(int)floor(x)] == '1'
			|| win->map.map[(int)ceil(y)][(int)ceil(x)] == '1')
			win->mov.hit = 1;
		win->mov.hit = 1;
	}
	else
	{
		win->mov.hit = 0;
		return (0);
	}
	return (1);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int		px_color(t_tex *tex, double y, double x, int id)
{
	if (id == N_WALL || id == E_WALL)
		return (*(int*)(tex->data + (tex->line_len * (int)y) +
			(4 * tex->tex_w) - (((int)x + 1) * 4)));
	else
		return (*(int*)(tex->data + (tex->line_len * (int)y) +
			(4 * (int)x)));
}
