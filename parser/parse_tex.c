/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:04:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/25 10:10:33 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
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
	win->tex.n_wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.n_wall)
		close_error("Invalid texture\n");
	win->tex.dn_wall = mlx_get_data_addr(win->tex.n_wall, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.dn_wall)
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
	win->tex.s_wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.s_wall)
		close_error("Invalid texture\n");
	win->tex.ds_wall = mlx_get_data_addr(win->tex.s_wall, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.ds_wall)
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
	win->tex.e_wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.e_wall)
		close_error("Invalid texture\n");
	win->tex.de_wall = mlx_get_data_addr(win->tex.e_wall, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.de_wall)
		close_error("Couldn't get texture data\n");
	free(path);
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
	win->tex.w_wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex.tex_w, &win->tex.tex_h);
	if (!win->tex.w_wall)
		close_error("Invalid texture\n");
	win->tex.dw_wall = mlx_get_data_addr(win->tex.w_wall, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	if (!win->tex.dw_wall)
		close_error("Couldn't get texture data\n");
	free(path);
}