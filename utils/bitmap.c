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
#include <unistd.h>
#include <utils.h>
#include <cub3d.h>

static int		image_size(int w, int h)
{
	int		per_line;

	per_line = w * 3;
	if (per_line % 4 != 0)
		per_line += 4 - (per_line % 4);
	return (per_line * h);
}

static void		write_header(int fd, int w, int h)
{
	int		total_size;

	write(fd, "BM", 2);
	total_size = 54 + image_size(w, h);
	write(fd, &total_size, 4);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write(fd, &w, 4);
	write(fd, &h, 4);
	write(fd, "\x01\0\x18\0\0\0\0\0\0\0\0\0\0\0\0\0\
	\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

static void		write_rgb(int fd, t_win *win)
{
	int		x;
	int		y;
	int		pad;
	int		rgb;

	x = 0;
	y = win->y - 1;
	pad = (4 - (win->x * 3) % 4) % 4;
	while (y >= 0)
	{
		while (x < win->x)
		{
			rgb = get_px(&win->img[0], x, y);
			write(fd, &rgb, 3);
			x++;
		}
		x = 0;
		write(fd, &x, pad);
		y--;
	}
}

void			save_frame(t_win *win)
{
	int	fd;

	win->save = 0;
	fd = open(BMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
		close_error("Can't create bitmap file\n");
	write_header(fd, win->x, win->y);
	write_rgb(fd, win);
	close(fd);
	close_win(win);
}
