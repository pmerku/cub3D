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

static void	parse_sprite(char *data, t_win *win, int i, int id)
{
	char *path;

	while (*data && (*data == ' '))
		data++;
	path = ft_strdup(data);
	malloc_check(path);
	while (win->spr[i].tex != NULL)
		i++;
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
	win->spr[i].id = id + win->color.spr_i; // ID for tex (for now only works if sprite tex are before everything)
}

void		parse_sprites(char *data, t_win *win)
{
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"S "))
		parse_sprite(data + 2, win, win->color.spr_i, SPR_T);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SM"))
		parse_sprite(data + 2, win, win->color.spr_i, SPR_M);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SI"))
		parse_sprite(data + 2, win, win->color.spr_i, SPR_I);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SC"))
		parse_sprite(data + 2, win, win->color.spr_i, SPR_C);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"ST"))
		parse_sprite(data + 2, win, win->color.spr_i, SPR_TR); // TODO: maybe this doesnt work
	if (win->color.spr_i >= S_NUM)
		close_error("Too many sprites\n");
	win->color.spr_i++;
}

static void sprite_pos(t_win *win, int i, int x, int y)
{
	win->spr[i].x = x;
	win->spr[i].y = y;
}

static void	sprite_save(t_win *win, int y, int x, char c)
{
	int		i;

	i = 0;
	if (ft_strchr(SPR_2_SET, c))
		sprite_pos()
}

void		sprite_set(t_win *win)
{
	int		x;
	int 	y;
	int 	i;

	y = 0;
	i = 0;
	while (y < win->map.map_h)
	{
		x = 0;
		while (x < win->map.map_w)
		{
			if (ft_strchr(SPRITE_SET, win->map.map[y][x]))
			{
				sprite_save(win, y, x, win->map.map[y][x]);
				i++;
			}
			x++;
		}
		y++;
	}
	win->color.spr_i = i;
}