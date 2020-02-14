/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 18:01:28 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <engine.h>
#include <cub3d.h>

int		query_map(t_win *win, double y, double x)
{
	if (y < 0 || y >= win->map.map_h || x < 0
		|| x >= ft_strlen(win->map.map[(int)y])
		|| ft_strchr(HIT_C, win->map.map[(int)y][(int)x]))
	{
		win->mov.hit = 1;
		if (ft_strchr(HIT_NC, win->map.map[(int)y][(int)x])
			|| open_door(win, y, x))
			return (0);
	}
	else if (ft_strchr(HIT_NC, win->map.map[(int)y][(int)x]))
	{
		win->mov.hit = 0;
		return (0);
	}
	return (1);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	*(unsigned int*)(img->addr
		+ (y * img->line_len + x * (img->bpp / 8))) = color;
}

int		px_color(t_tex *tex, double y, double x, int id)
{
	if (x >= 0 && x < tex->tex_w && y >= 0 && y < tex->tex_h)
	{
		if (id == N_WALL || id == E_WALL)
			return (*(int*)(tex->data + (tex->line_len * (int)y) +
				(4 * tex->tex_w) - (((int)x + 1) * 4)));
		else
			return (*(int*)(tex->data + (tex->line_len * (int)y) +
				(4 * (int)x)));
	}
	return (0x0);
}

void	sprite_hide(t_win *win, double y, double x)
{
	if (ft_strchr(HIT_P, win->map.map[(int)y][(int)x]))
	{
		win->map.map[(int)y][(int)x] = '0';
		win->spr[win->spr_i - 1].hide = 1;
	}
}

int		open_door(t_win *win, double y, double x)
{
	if (win->key.open)
	{
		if (win->map.map[(int)y][(int)x] == 'D')
			win->mov.hit = !win->mov.hit;
		return (1);
	}
	return (0);
}