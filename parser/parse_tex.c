/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:04:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/25 12:25:46 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <engine.h>
#include <cub3d.h>

void	parse_nw(char **data, t_win *win, int *i)
{
	int 	j;
	char	*path;

	j = 2;
	while (data[*i][j] && data[*i][j] == ' ')
		j++;
	path = ft_strdup(data[*i] + j);
	if (!path)
		close_error("Malloc error\n");
	win->tex.wall[N_WALL] = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.wall[N_WALL])
		close_error("Invalid texture\n");
	win->tex.data[N_WALL] = mlx_get_data_addr(win->tex.wall[S_WALL], &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.data[N_WALL])
		close_error("Couldn't get texture data\n");
	free(path);
}

void	parse_sw(char **data, t_win *win, int *i)
{
	int 	j;
	char	*path;

	j = 2;
	while (data[*i][j] && data[*i][j] == ' ')
		j++;
	path = ft_strdup(data[*i] + j);
	if (!path)
		close_error("Malloc error\n");
	win->tex.wall[S_WALL] = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.wall[S_WALL])
		close_error("Invalid texture\n");
	win->tex.data[S_WALL] = mlx_get_data_addr(win->tex.wall[S_WALL], &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.data[S_WALL])
		close_error("Couldn't get texture data\n");
	free(path);
}

void	parse_ew(char **data, t_win *win, int *i)
{
	int 	j;
	char	*path;

	j = 2;
	while (data[*i][j] && data[*i][j] == ' ')
		j++;
	path = ft_strdup(data[*i] + j);
	if (!path)
		close_error("Malloc error\n");
	win->tex.wall[E_WALL] = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.wall[E_WALL])
		close_error("Invalid texture\n");
	win->tex.data[E_WALL] = mlx_get_data_addr(win->tex.wall[E_WALL], &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.data[N_WALL])
		close_error("Couldn't get texture data\n");
	free(path); // TODO: maybe recode how the texture are saved
}

void	parse_ww(char **data, t_win *win, int *i)
{
	int 	j;
	char	*path;

	j = 2;
	while (data[*i][j] && data[*i][j] == ' ')
		j++;
	path = ft_strdup(data[*i] + j);
	if (!path)
		close_error("Malloc error\n");
	win->tex.wall[W_WALL] = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.wall[W_WALL])
		close_error("Invalid texture\n");
	win->tex.data[W_WALL] = mlx_get_data_addr(win->tex.wall[W_WALL], &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.data[W_WALL])
		close_error("Couldn't get texture data\n");
	free(path);
}