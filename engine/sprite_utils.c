/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:42:02 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 11:16:42 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void 			sprite_dist(t_win *win)
{
	int		i;

	i = 0;
	while (i < win->spr_i)
	{
		win->spr[i].dist = sqrt((double)pow(win->pos.x - win->spr[i].x, 2)
				+ (double)pow(win->pos.y - win->spr[i].y, 2));
		i++;
	}
}

static void	sprite_dup(t_spr *dst, t_spr *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->tex_id = src->tex_id;
	dst->dist = src->dist;
}

static void	sprite_swap(t_spr *left, t_spr *right)
{
	t_spr	tmp;

	sprite_dup(&tmp, left);
	sprite_dup(left, right);
	sprite_dup(right, &tmp);
}

void		sprite_sort(t_spr *spr, int first, int last)
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
				j--;
			if (i < j)
				sprite_swap(&spr[i], &spr[j]);
		}
		sprite_swap(&spr[tmp], &spr[j]);
		sprite_sort(spr, first, j - 1);
		sprite_sort(spr, j + 1, last);
	}
}