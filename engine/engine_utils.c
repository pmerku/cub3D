/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/19 10:25:02 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>
#include <cub3d.h>

/*
** Put pixel color on image x/y position
**
** @param  t_img  *img allocated image structure
** @param  int       x pos x on image
** @param  int       y position y on image
** @param  int   color color value
** @return void
*/

void		pixel_put(t_img *img, int x, int y, int color)
{
	*(unsigned int*)(img->addr
		+ (y * img->line_len + x * (img->bpp / 8))) = color;
}

/*
** Get pixel color from x/y position in texture
**
** @param  t_tex  *tex allocated texture structure
** @param  double    y pos y in texture image
** @param  double    x position x in texture image
** @param  int      id texture id
** @return int         pixel color value
*/

int			px_color(t_tex *tex, double y, double x, int id)
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

/*
** Which sprite is picked up
**
** @param  t_win  *win allocated global window structure
** @param  double    y pos y of player
** @param  double    x position x of player
** @param  int       i sprite index
** @return void
*/

static void	sprite_get(t_win *win, double y, double x, int i)
{
	while (i < win->spr_i)
	{
		if ((int)win->spr[i].x == (int)x && (int)win->spr[i].y == (int)y)
		{
			win->map.map[(int)y][(int)x] = '0';
			win->spr[i].hide = 1;
			return ;
		}
		i++;
	}
}

/*
** Hide sprite if you can pick it up, play according sound and change score
**
** @param  t_win  *win allocated global window structure
** @param  double    y pos y of player
** @param  double    x position x of player
** @return void
*/

void		sprite_hide(t_win *win, double y, double x)
{
	if (!ft_strchr(HIT_P, win->map.map[(int)y][(int)x]))
		return ;
	if (win->map.map[(int)y][(int)x] == 'T')
	{
		sound_effect("./sound/damage.wav");
		win->health -= 1. / 3;
	}
	else
	{
		if (win->map.map[(int)y][(int)x] == 'P')
		{
			sound_effect("./sound/pickup.wav");
			win->score += 1. / win->spr_p;
		}
		else
		{
			sound_effect("./sound/health.wav");
			if (win->health != 1)
				win->health += 1. / 3;
		}
	}
	sprite_get(win, y, x, 0);
}

/*
** Open door on correct key press
**
** @param  t_win  *win allocated global window structure
** @param  double    y pos y of player
** @param  double    x position x of player
** @return int         status code
*/

int			open_door(t_win *win, double y, double x)
{
	if (win->key.open)
		if (win->map.map[(int)y][(int)x] == 'D')
		{
			win->mov.hit = !win->mov.hit;
			return (1);
		}
	return (0);
}
