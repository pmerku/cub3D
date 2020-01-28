/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:04:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/28 10:45:46 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>
#include <engine.h>
#include <cub3d.h>
// TODO: norm
// TODO: maybe recode how the texture are saved
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
	win->tex[N_WALL].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[N_WALL].tex_w, &win->tex[N_WALL].tex_h);
	if (!win->tex[N_WALL].wall)
		close_error("Invalid texture\n");
	win->tex[N_WALL].data = mlx_get_data_addr(win->tex[N_WALL].wall, &win->tex[N_WALL].bpp,
			&win->tex[N_WALL].line_len, &win->tex[N_WALL].endian);
	if (!win->tex[N_WALL].data)
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
	win->tex[S_WALL].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[S_WALL].tex_w, &win->tex[S_WALL].tex_h);
	if (!win->tex[S_WALL].wall)
		close_error("Invalid texture\n");
	win->tex[S_WALL].data = mlx_get_data_addr(win->tex[S_WALL].wall, &win->tex[S_WALL].bpp,
			&win->tex[S_WALL].line_len, &win->tex[S_WALL].endian);
	if (!win->tex[S_WALL].data)
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
	win->tex[E_WALL].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[E_WALL].tex_w, &win->tex[E_WALL].tex_h);
	if (!win->tex[E_WALL].wall)
		close_error("Invalid texture\n");
	win->tex[E_WALL].data = mlx_get_data_addr(win->tex[E_WALL].wall, &win->tex[S_WALL].bpp,
			&win->tex[S_WALL].line_len, &win->tex[S_WALL].endian);
	if (!win->tex[E_WALL].data)
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
	win->tex[W_WALL].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[W_WALL].tex_w, &win->tex[W_WALL].tex_h);
	if (!win->tex[W_WALL].wall)
		close_error("Invalid texture\n");
	win->tex[W_WALL].data = mlx_get_data_addr(win->tex[W_WALL].wall, &win->tex[W_WALL].bpp,
			&win->tex[W_WALL].line_len, &win->tex[W_WALL].endian);
	if (!win->tex[W_WALL].data)
		close_error("Couldn't get texture data\n");
	free(path);
}
