/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:53:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/18 11:36:38 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_memory.h>
#include "utils.h"
#include "cub3d.h"

/**
 * Save sprite position
 * @param win global game structure
 * @param c sprite character
 * @param pos sprite id
 * @return status code (if not zero, sprite texture is missing)
 */
static int	sprite_pos(t_win *win, const char c, int *pos) {
	for (int i = 0; i < S_NUM; i++) {
		if (win->type[i].c == c) {
			win->spr[*pos].x = win->pos.tmp_x + .5;
			win->spr[*pos].y = win->pos.tmp_y + .5;
			win->spr[*pos].tex_id = win->type[i].tex_i;
			win->spr[*pos].hide = 0;
			(*pos)++;
			return 1;
		}
	}
	return 0;
}

/**
 * Scan map for the sprite position
 * @param win
 */
static void	save_sprite(t_win *win) {
	int	pos = 0;
	for (int y = 0; y < win->map.map_h; y++) {
		for (int x = 0; win->map.map[y][x]; x++) {
			if (ft_strchr(SPRITE_SET, win->map.map[y][x])) {
				win->pos.tmp_x = x;
				win->pos.tmp_y = y;
				if (!sprite_pos(win, win->map.map[y][x], &pos))
					close_error("Missing texture for the sprite\n");
			}
		}
	}
}

/**
 * Check if sprite texture is loaded
 * @param win
 * @param c
 * @return status code
 */
static int	sprite_on(t_win *win, char c) {
	for (int i = 0; i < S_NUM; i++) {
		if (win->type[i].c == c) {
			if (c == 'P')
				win->spr_p++;
			if (win->tex[win->type[i].tex_i].wall == NULL)
				close_error("Missing textures\n");
			return 1;
		}
	}
	return 0;
}

/**
 * Set sprite ids
 * @param win global game structure
 */
static void	sprite_init(t_win *win) {
	win->type[0].c = 'I';
	win->type[0].tex_i = SPR_I;
	win->type[1].c = 'P';
	win->type[1].tex_i = SPR_P;
	win->type[2].c = 'T';
	win->type[2].tex_i = SPR_TR;
	win->type[3].c = '2';
	win->type[3].tex_i = SPR_T2;
	win->type[4].c = '3';
	win->type[4].tex_i = SPR_T3;
	win->type[5].c = '4';
	win->type[5].tex_i = SPR_T1;
	win->type[6].c = '5';
	win->type[6].tex_i = SPR_T4;
	win->type[7].c = 'M';
	win->type[7].tex_i = SPR_M;
}

/**
 * Load sprites data
 * @param win global game structure
 */
void		sprite_set(t_win *win) {
	sprite_init(win);
	for (int y = 0; y < win->map.map_h; y++) {
		for (int x = 0; win->map.map[y][x]; x++) {
			if (ft_strchr(SPRITE_SET, win->map.map[y][x])) {
				if (!sprite_on(win, win->map.map[y][x]))
					close_error("Missing sprite texture\n");
				win->spr_i++;
			}
		}
	}
	win->spr = ft_calloc(win->spr_i, sizeof(t_spr));
	malloc_check(win->spr);
	save_sprite(win);
}
