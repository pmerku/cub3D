/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/14 15:13:49 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <utils.h>
#include <cub3d.h>

/*
** Fork process and play sound in background
**
** @param  char *cmd path to sound file
** @return int       status code
*/

int		sound(char *cmd)
{
	if (fork() < 0)
		exit(EXIT_FAILURE);
	else
	{
		cmd = ft_strjoin_free2("afplay ", cmd);
		system(cmd);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
}

/*
** Put pixel color on image x/y position
**
** @param  t_img  *img allocated image structure
** @param  int       x pos x on image
** @param  int       y position y on image
** @param  int   color color value
** @return void
*/

void	pixel_put(t_img *img, int x, int y, int color)
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

/*
** Hide sprite if you can pick it up, play according sound and change score
**
** @param  t_win  *win allocated global window structure
** @param  double    y pos y of player
** @param  double    x position x of player
** @return void
*/

void	sprite_hide(t_win *win, double y, double x)
{
	if (ft_strchr(HIT_P, win->map.map[(int)y][(int)x]))
	{
		if (win->map.map[(int)y][(int)x] == 'T')
		{
			if (sound("damage.wav") == 1)
				close_error("Sound error\n");
			win->health -= (double)1 / 3;
		}
		else
		{
			if (sound("point.wav") == 1)
				close_error("Sound error\n");
			win->score += (double)1 / win->spr_i;
		}
		win->map.map[(int)y][(int)x] = '0';
		win->spr[win->spr_i - 1].hide = 1;
	}
}

/*
** Open door on correct key press
**
** @param  t_win  *win allocated global window structure
** @param  double    y pos y of player
** @param  double    x position x of player
** @return int         status code
*/

int		open_door(t_win *win, double y, double x)
{
	if (win->key.open)
		if (win->map.map[(int)y][(int)x] == 'D')
		{
			win->mov.hit = !win->mov.hit;
			return (1);
		}
	return (0);
}