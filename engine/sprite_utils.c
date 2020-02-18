/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:42:02 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/17 15:14:04 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <cub3d.h>

/*
** Copy over sprite structure values
**
** @param  t_spr  *dst allocated sprite structure
** @param  t_spr  *src allocated sprite structure
** @return void
*/

static void	sprite_dup(t_spr *dst, t_spr *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->tex_id = src->tex_id;
	dst->dist = src->dist;
	dst->hide = src->hide;
}

/*
** Swap sprites
**
** @param  t_spr  *left allocated sprite structure
** @param  t_spr  *right allocated sprite structure
** @return void
*/

static void	sprite_swap(t_spr *left, t_spr *right)
{
	t_spr	tmp;

	sprite_dup(&tmp, left);
	sprite_dup(left, right);
	sprite_dup(right, &tmp);
}

/*
** Sprite sorting algorithm
**
** @param  t_spr  *spr allocated sprite structure
** @param  int   first first sprite index
** @param  int    last last sprite index
** @return void
*/

void		sprite_sort(t_spr *spr, int first, int last)
{
	int		i;
	int		j;
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
				j--;
			if (i < j)
				sprite_swap(&spr[i], &spr[j]);
		}
		sprite_swap(&spr[tmp], &spr[j]);
		sprite_sort(spr, first, j - 1);
		sprite_sort(spr, j + 1, last);
	}
}

/*
** Calculations for sprite distance from player
**
** @param  t_win *win allocated global window structure
** @return void
*/



void		sprite_dist(t_win *win)
{
	int		i;

	i = 0;
	while (i < win->spr_i)
	{
		win->spr[i].dist = sqrt((double)pow(win->pos.x - win->spr[i].x, 2)
				+ (double)pow(win->pos.y - win->spr[i].y, 2));
		i++;
	}
	sprite_sort(win->spr, 0, win->spr_i - 1);
}
