/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:50:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 14:58:02 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

static u_char	*bitmap_header(int h, int w, int pad_s)
{
	static u_char	header[BMP_HSIZE];
	u_int			file_s;

	file_s = BMP_HSIZE + BMP_ISIZE + (BMP_BPP * w + pad_s) * h;
	header[0] = (u_char)('B');
	header[1] = (u_char)('M');
	header[2] = (u_char)(file_s);
	header[3] = (u_char)(file_s >> 8U);
	header[4] = (u_char)(file_s >> 16U);
	header[5] = (u_char)(file_s >> 24U);
	header[10] = (u_char)(BMP_HSIZE + BMP_ISIZE);
	return (header);
}

static u_char	*bitmap_info(u_int h, u_int w)
{
	static u_char	header[BMP_ISIZE];

	header[0] = (u_char)(BMP_ISIZE);
	header[4] = (u_char)(w);
	header[5] = (u_char)(w >> 8U);
	header[6] = (u_char)(w >> 16U);
	header[7] = (u_char)(w >> 24U);
	header[8] = (u_char)(h);
	header[9] = (u_char)(h >> 8U);
	header[10] = (u_char)(h >> 16U);
	header[11] = (u_char)(h >> 24U);
	header[12] = (u_char)(1);
	header[14] = (u_char)(BMP_BPP * 8);
	return (header);
}

static void		save_bitmap(u_char *img, int h, int w)
{
	u_char	pad[3];
	int 	pad_s;
	int		img_f;

	img_f = open(BMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0755);
	pad_s = (4 - (w * BMP_BPP) % 4) % 4;
	write(img_f, bitmap_header(h, w, pad_s), BMP_HSIZE);
	write(img_f, bitmap_info(h, w), BMP_ISIZE);
	while (h >= 0)
	{
		write(img_f, img + (BMP_BPP * w * h), BMP_BPP * w);
		write(img_f, pad, pad_s);
		h--;
	}
	close(img_f);
}

static void		set_px(t_win *win, int x, int y, u_char *img, int i)
{
	u_char	*ptr;

	ptr = img + (BMP_BPP * win->x * y) + (x * BMP_BPP) + i;
	if (i == 0)
		*ptr = get_b(win->color.bmp_color);
	else if (i == 1)
		*ptr = get_g(win->color.bmp_color);
	else if (i == 2)
		*ptr = get_r(win->color.bmp_color);
}

void			save_frame(t_win *win)
{
	u_char	*img;

	win->pos.tmp_y = 0;
	win->save = 0;
	img = ft_calloc(win->y * win->x, BMP_BPP);
	malloc_check(img);
	while (win->pos.tmp_y < win->y)
	{
		win->pos.tmp_x = 0;
		while (win->pos.tmp_x < win->x)
		{
			win->color.bmp_color = get_px(&win->img[win->i], (int)win->pos.tmp_x, (int)win->pos.tmp_y);
			set_px(win, (int)win->pos.tmp_x, (int)win->pos.tmp_y, img, 0);
			set_px(win, (int)win->pos.tmp_x, (int)win->pos.tmp_y, img, 1);
			set_px(win, (int)win->pos.tmp_x, (int)win->pos.tmp_y, img, 2);
			win->pos.tmp_x++;
		}
		win->pos.tmp_y++;
	}
	save_bitmap((u_char *)img, win->y, win->x);
}