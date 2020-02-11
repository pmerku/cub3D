/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:26:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/11 16:50:11 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

static double	calc_dist(double x0, double y0, double x1, double y1)
{
	return (sqrt((double)pow(x1 - x0, 2) + (double)pow(y1 - y0, 2)));
}

static void sprite_dist(t_win *win)
{
	int		i;

	i = 0;
	while (i < win->spr_i)
	{
		win->spr[i].dist = calc_dist(win->spr[i].x, win->spr[i].y, win->pos.x, win->pos.y);
		i++;
	}
}

static void	sprite_dup(t_spr *dst, t_spr *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->tex_id = src->tex_id;
	dst->dist = src->dist;
	dst->hid = src->hid;
}

static void	sprite_swap(t_spr *left, t_spr *right)
{
	t_spr	tmp;

	sprite_dup(&tmp, left);
	sprite_dup(left, right);
	sprite_dup(right, &tmp);
}

static void	sprite_sort(t_spr *spr, int first, int last)
{
	int 	i;
	int 	j;
	int		tmp;

	if (first < last)
	{
		tmp = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (spr[i].dist >= spr[tmp].dist && i < last)
				i++;
			while (spr[j].dist < spr[tmp].dist)
				i--;
			if (i < j)
				sprite_swap(&spr[i], &spr[j]);
		}
		sprite_swap(&spr[tmp], &spr[j]);
		sprite_sort(spr, first, j - 1);
		sprite_sort(spr, j + 1, last);
	}
}

void	draw_sprite(t_win *win)
{
	int 	x;
	int 	stripe;
	int 	y;

	sprite_dist(win);
	sprite_sort(win->spr, 0, win->spr_i - 1);
	x = 0;
	while (x < win->spr_i)
	{
		double spriteX = win->spr[x].x - win->pos.x;
		double spriteY = win->spr[x].y - win->pos.y;

		double invDet = 1. / (win->pos.plane_x * win->pos.dir_y - win->pos.dir_x * win->pos.plane_y);

		double transX = invDet * (win->pos.dir_y * spriteX - win->pos.dir_x * spriteY);
		double transY = invDet * (-win->pos.plane_y * spriteX - win->pos.plane_x * spriteY);

		int sprSX = (int)(win->x / 2) * (1 + transX / transY);

		int sprH = abs((int)(win->y / transY));
		int draw_sY = -sprH / 2 + win->y / 2;
		if (draw_sY < 0)
			draw_sY = 0;
		int draw_eY = sprH / 2 + win->y / 2;
		if (draw_eY >= win->y)
			draw_eY = win->y - 1;

		int sprW = abs((int)(win->y / transY));
		int draw_sX = -sprW / 2 + sprSX;
		if (draw_sX < 0)
			draw_sX = 0;
		int draw_eX = sprW / 2 + sprSX;
		if (draw_eX >= win->x)
			draw_eX = win->x - 1;

		stripe = draw_sX;
		while (stripe < draw_eX)
		{
			int tex_X = (int)(256 * (stripe - (-sprW / 2 + sprSX)) * win->tex[win->spr[x].tex_id].tex_w / sprW) / 256;
			if (transY > 0 && stripe > 0 && stripe < win->x && transY < win->z_buff[stripe])
			{
				y = draw_sY;
				while (y < draw_eY)
				{
					int d = y * 256 - win->y * 128 + sprH * 128;
					int tex_Y = ((d * win->tex[win->spr[x].tex_id].tex_h) / sprH) / 256;
					u_int color = px_color(&win->tex[win->spr[x].tex_id], tex_Y, tex_X, win->spr[x].tex_id);
					if (color != 0x0)
						pixel_put(&win->img[win->i], stripe, y, color);
					y++;
				}
			}
			stripe++;
		}
		x++;
	}
}