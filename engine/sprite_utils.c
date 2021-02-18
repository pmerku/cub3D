/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:42:02 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/19 08:22:16 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

/**
 * Copy over sprites structure values
 * @param dst sprite structure
 * @param src sprite structure
 */
static void	sprite_dup(t_spr *dst, t_spr *src) {
	dst->x = src->x;
	dst->y = src->y;
	dst->tex_id = src->tex_id;
	dst->dist = src->dist;
	dst->hide = src->hide;
}

/**
 * Swap sprites data
 * @param left sprite structure
 * @param right sprite structure
 */
static void	sprite_swap(t_spr *left, t_spr *right) {
	t_spr	tmp;

	sprite_dup(&tmp, left);
	sprite_dup(left, right);
	sprite_dup(right, &tmp);
}

/**
 * Sort sprites
 * @param spr sprites structure
 * @param first sprite index
 * @param last sprite index
 */
void		sprite_sort(t_spr *spr, int first, int last) {
	if (first < last) {
		int tmp = first;
		int i = first;
		int j = last;
		while (i < j) {
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

/**
 * Calculate sprite distance from player
 * @param win global game structure
 */
void		sprite_dist(t_win *win) {
	for (int i = 0; i < win->spr_i; i++)
		win->spr[i].dist = ((double)pow(win->pos.x - win->spr[i].x, 2) + (double)pow(win->pos.y - win->spr[i].y, 2));
	sprite_sort(win->spr, 0, win->spr_i - 1);
}
