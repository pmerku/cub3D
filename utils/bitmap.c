/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:50:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/19 08:15:54 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft_string.h>
#include <ft_unistd.h>
#include <ft_memory.h>
#include <unistd.h>
#include "utils.h"
#include "cub3d.h"

/**
 * Set bitmap header
 * @param h header height
 * @param w header width
 * @param pad_s header padding
 * @return header buffer
 */
static u_char	*bitmap_header(u_int h, u_int w, int pad_s) {
	static u_char	header[BMP_HSIZE];

	u_int file_s = BMP_HSIZE + BMP_ISIZE + (BMP_BPP * w + pad_s) * h;
	header[0] = (u_char)('B');
	header[1] = (u_char)('M');
	header[2] = (u_char)(file_s);
	header[3] = (u_char)(file_s >> 8);
	header[4] = (u_char)(file_s >> 16);
	header[5] = (u_char)(file_s >> 24);
	header[10] = (u_char)(BMP_HSIZE + BMP_ISIZE);
	return header;
}

/**
 * Set bitman info
 * @param h info height
 * @param w info width
 * @return info buffer
 */
static u_char	*bitmap_info(u_int h, u_int w) {
	static u_char	header[BMP_ISIZE];

	header[0] = (u_char)(BMP_ISIZE);
	header[4] = (u_char)(w);
	header[5] = (u_char)(w >> 8);
	header[6] = (u_char)(w >> 16);
	header[7] = (u_char)(w >> 24);
	header[8] = (u_char)(h);
	header[9] = (u_char)(h >> 8);
	header[10] = (u_char)(h >> 16);
	header[11] = (u_char)(h >> 24);
	header[12] = (u_char)(1);
	header[14] = (u_char)(BMP_BPP * 8);
	return header;
}

/**
 * Create bitmap header
 * @param img bitmap image
 * @param h image height
 * @param w image width
 */
static void		save_bitmap(u_char *img, int h, int w) {
	u_char	pad[3];

	int img_f = open(BMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0755);
	int pad_s = (4 - (w * BMP_BPP) % 4) % 4;
	ft_write(img_f, bitmap_header(h, w, pad_s), BMP_HSIZE);
	ft_write(img_f, bitmap_info(h, w), BMP_ISIZE);
	h -= 1;
	while (h >= 0) {
		ft_write(img_f, img + (BMP_BPP * w * h), BMP_BPP * w);
		ft_write(img_f, pad, pad_s);
		h--;
	}
	close(img_f);
}

/**
 * Set pixel color
 * @param win global game structure
 * @param img bitmap image
 * @param i color id
 */
static void		set_px(t_win *win, u_char *img, int i) {
	u_char *ptr = img + (int)(BMP_BPP * win->x * (int)win->bmp_y) + ((int)win->bmp_x * BMP_BPP) + i;
	if (i == 0)
		*ptr = get_b(win->color.bmp_color);
	else if (i == 1)
		*ptr = get_g(win->color.bmp_color);
	else if (i == 2)
		*ptr = get_r(win->color.bmp_color);
}

/**
 * Save frame as bitmap
 * @param win global game structure
 */
void			save_frame(t_win *win) {
	win->bmp_y = 0;
	u_char *img = ft_calloc(win->y * win->x, BMP_BPP);
	malloc_check(img);
	while (win->bmp_y < win->y) {
		win->bmp_x = 0;
		while (win->bmp_x < win->x) {
			win->color.bmp_color = get_px(&win->img[win->i], (int)win->bmp_x, (int)win->bmp_y);
			set_px(win, img, 0);
			set_px(win, img, 1);
			set_px(win, img, 2);
			win->bmp_x++;
		}
		win->bmp_y++;
	}
	save_bitmap((u_char *)img, win->y, win->x);
	close_win(win);
}
