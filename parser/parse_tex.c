/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:04:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/29 15:29:00 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <engine.h>
#include <cub3d.h>

void	parse_w(char **data, t_win *win, int i, int index)
{
	int 	j;
	char	*path;

	j = 2;
	while (data[i][j] && (data[i][j] == ' '))
		j++;
	path = ft_strdup(data[i] + j);
	malloc_check(path);
	win->tex[index].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[index].tex_w, &win->tex[index].tex_h);
	if (!win->tex[index].wall)
		close_error("Invalid texture\n");
	win->tex[index].data = mlx_get_data_addr(win->tex[index].wall,
			&win->tex[index].bpp,
			&win->tex[index].line_len,
			&win->tex[index].endian);
	if (!win->tex[index].data)
		close_error("Couldn't get texture data\n");
	free(path);
}
