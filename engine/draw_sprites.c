/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:26:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 12:18:18 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <engine.h>

/**
 * Draw sprites textures
 * @param win global game structure
 * @param tex sprite texture
 * @param sdt sprite raycastin structure
 * @param id sprite id
 */
static void	sprite_tex(t_win *win, t_tex *tex, t_sdt *sdt, int id) {
	tex->tex_x = (int)(256 * (sdt->draw_sx - (-sdt->spr_d / 2 + sdt->spr_sx)) * tex->tex_w / sdt->spr_d) / 256;
	if (sdt->trs_y >= 0 && sdt->draw_sx >= 0 && sdt->draw_sx <= win->x && sdt->trs_y <= win->z_buff[sdt->draw_sx]) {
		for (int y = sdt->draw_sy; y <= sdt->draw_ey; y++) {
			sdt->d = y * 256 - win->y * 128 + sdt->spr_d * 128;
			tex->tex_y = ((sdt->d * tex->tex_h) / sdt->spr_d) / 256;
			u_int color = px_color(tex, tex->tex_y, tex->tex_x, id);
			if (color != 0x0)
				pixel_put(&win->img[win->i], sdt->draw_sx, y, color);
		}
	}
}

/**
 * Sprites raycasting
 * @param win global game structure
 * @param sdt sprites raycasting structure
 * @param i vertical image line
 */
void		draw_sprite(t_win *win, t_sdt *sdt) {
	for (int i = 0; i < win->spr_i; i++) {
		if (win->spr[i].hide == 0) {
			sdt->spr_x = win->spr[i].y - win->pos.y;
			sdt->spr_y = win->spr[i].x - win->pos.x;
			sdt->inv_d = 1.0 / (win->pos.plane_x * win->pos.dir_y - win->pos.dir_x * win->pos.plane_y);
			sdt->trs_x = sdt->inv_d * (win->pos.dir_y * sdt->spr_x - win->pos.dir_x * sdt->spr_y);
			sdt->trs_y = sdt->inv_d * (-win->pos.plane_y * sdt->spr_x + win->pos.plane_x * sdt->spr_y);
			sdt->spr_sx = (int)((win->x / 2.) * (1 + sdt->trs_x / sdt->trs_y));
			sdt->spr_d = abs((int)(win->y / sdt->trs_y));
			sdt->draw_sy = -sdt->spr_d / 2 + win->y / 2;
			sdt->draw_sy = (sdt->draw_sy < 0) ? 0 : sdt->draw_sy;
			sdt->draw_ey = sdt->spr_d / 2 + win->y / 2;
			sdt->draw_ey = (sdt->draw_ey >= win->y) ? win->y - 1 : sdt->draw_ey;
			sdt->draw_sx = -sdt->spr_d / 2 + sdt->spr_sx;
			sdt->draw_sx = (sdt->draw_sx < 0) ? 0 : sdt->draw_sx;
			sdt->draw_ex = sdt->spr_d / 2 + sdt->spr_sx;
			sdt->draw_ex = (sdt->draw_ex >= win->x) ? win->x - 1 : sdt->draw_ex;
			for (; sdt->draw_sx <= sdt->draw_ex; sdt->draw_sx++)
				sprite_tex(win, &win->tex[win->spr[i].tex_id], sdt, win->spr[i].tex_id);
		}
	}
}
