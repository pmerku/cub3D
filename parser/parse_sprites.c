/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:53:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/07 12:15:59 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <cub3d.h>

static void	parse_sprite(char *path, t_win *win, int i)
{
	win->spr[i].tex = mlx_png_file_to_image(win->mlx, path,
			&win->spr[i].tex_w, &win->spr[i].tex_h);
	if (!win->spr[i].tex)
	{
		free(path);
		close_error("Invalid texture\n");
	}
	win->spr[i].data = mlx_get_data_addr(win->spr[i].tex,
			&win->spr[i].bpp, &win->spr[i].line_len, &win->spr[i].endian);
	if (!win->spr[i].data)
	{
		free(path);
		close_error("Couldn't get texture data\n");
	}
}

void		parse_sprites(char *data, t_win *win)
{
	char	*path;

	data += 2;
	while (*data && (*data == ' '))
		data++;
	path = ft_strdup(data);
	malloc_check(path);
	parse_sprite(path, win, win->color.spr_i);
	if (win->color.spr_i >= S_NUM)
		close_error("Too many sprites\n");
	win->color.spr_i++;
	free(path);
}