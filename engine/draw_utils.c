/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 11:02:17 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// TODO: maybe redo the map checking (add offset/hit box)

int		query_map(t_win *win, double y, double x)
{
	if (y < 0 || y >= win->map.map_h || x < 0 || x >= win->map.map_w
		|| win->map.map[(int)y][(int)x] == '1'
		|| win->map.map[(int)y][(int)x] == 'H')
	{
		win->mov.hit = 1;
		if (win->map.map[(int)y][(int)x] == 'H')
			return (0);
	}
	else if (win->map.map[(int)y][(int)x] == '0'
		|| win->map.map[(int)y][(int)x] == 'I'
		|| win->map.map[(int)y][(int)x] == 'C'
		|| win->map.map[(int)y][(int)x] == '4')
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
