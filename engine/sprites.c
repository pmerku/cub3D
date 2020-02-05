/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:26:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/05 15:35:44 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

void	draw_sprite(t_win *win, int i)
{
	double spriteX = win->spr.x - win->pos.x;
	double spriteY = win->spr.y - win->pos.y;

	double invDet = 1. / (win->pos.plane_x * win->ray.dir_y - win->pos.plane_y * win->ray.dir_x);

	double transformX = invDet * (win->ray.dir_y * spriteX - win->ray.dir_x * spriteY);
	double transformY = invDet * (-win->pos.plane_y * spriteX + win->pos.plane_x * spriteY);

	int spriteScreenX = (int)((win->x / 2) * (1 + transformX / transformY));

	int spriteH = abs((int)(win->y / transformY));
	int drawSY = -spriteH / 2 + win->y / 2;
	if (drawSY < 0)
		drawSY = 0;
	int drawEY = spriteH / 2 + win->y / 2;
	if (drawEY > win->y)
		drawEY = win->y - 1;

	int spriteW = abs((int)(win->y / transformY));
	int drawSX = -spriteW / 2 + spriteScreenX;
	if(drawSX < 0)
		drawSX = 0;
	int drawEX = spriteW / 2 + spriteScreenX;
	if(drawEX >= win->x)
		drawEX = win->x - 1;

	for(int stripe = drawSX; stripe < drawEX; stripe++)
	{
		win->tex[SPRITE].tex_x = (int)(stripe * win->tex[SPRITE].tex_w) % win->tex[SPRITE].tex_w;
//		win->tex[SPRITE].tex_x = (int)(256 * (stripe - (-spriteW / 2 + spriteScreenX)) * win->tex[SPRITE].tex_w / spriteW) / 256;
		if (transformY > 0 && stripe > 0 && stripe < win->x && transformY < win->spr.zbuff[stripe])
		{
			int y = drawSY;
			while (y < drawEY)
			{
//				int d = y * 256 - win->y * 128 + spriteH * 128;
//				win->tex[SPRITE].tex_y = ((d * win->tex[SPRITE].tex_h) / spriteH) / 256;
				win->tex[SPRITE].tex_y = (int)(((y - win->y * .5 + win->img[win->i].line_h * .5)
					   * win->tex[SPRITE].tex_h) / win->img[win->i].line_h) % win->tex[SPRITE].tex_h;
				u_int color = px_color(&win->tex[SPRITE], SPRITE);
				if (color != 0x0)
					pixel_put(&win->img[win->i], i, y, color);
				y++;
			}
		}
	}
}