/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:19:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 09:42:45 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "engine.h"
#include "cub3d.h"

static void	draw_block(t_win *win, int y, u_int color)
{
	int		x0;
	int		x1;
	int		y0;
	int		y1;

	x0 = win->hud.x0 - 1;
	y0 = win->hud.y0 - 1;
	x1 = win->hud.x1 + 1;
	y1 = win->hud.y1 + 1;
	while (x0 < x1)
	{
		y = y0;
		while (y < y1)
		{
			pixel_put(&win->img[win->i], x0, y, color);
			y++;
		}
		x0++;
	}
}

static void	draw_score(t_win *win)
{
	win->hud.x0 = win->x - (2 * win->x / 3);
	win->hud.y0 = win->y - (win->y / 15);
	win->hud.x1 = win->x - (win->x / 3);
	win->hud.y1 = win->y - (win->y / 18);
	draw_block(win, win->hud.y0 - 1, 0x00A0A0FF);
	win->hud.x1 = win->hud.x0 + (win->hud.x1 - win->hud.x0) * win->score;
	if (win->hud.x1 - win->hud.x0 > 0)
		draw_block(win, win->hud.y0 - 1, (int)(0x00FFFF00 * win->score));
}

void		draw_hud(t_win *win)
{
	if (!win->mov.m_speed && win->sound)
	{
		win->sound = 0;
		write(1, "Game Over!\n", 11);
	}
	if (win->score >= 1 && win->sound)
	{
		win->sound = 0;
		write(1, "You Won!\n", 9);
	}
	if (!win->key.hud)
		return ;
	win->hud.x0 = win->x - (2 * win->x / 3);
	win->hud.y0 = win->y - (win->y / 20);
	win->hud.x1 = win->x - (win->x / 3);
	win->hud.y1 = win->y - (win->y / 35);
	draw_block(win, win->hud.y0 - 1, 0x00AA0000);
	win->hud.x1 = win->hud.x0 + (win->hud.x1 - win->hud.x0) * win->health;
	if (win->hud.x1 - win->hud.x0 > 0)
		draw_block(win, win->hud.y0 - 1, (int)(0x0000FF00 * win->health));
	draw_score(win);
}
