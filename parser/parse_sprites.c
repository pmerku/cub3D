/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 11:53:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/11 12:10:04 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>
#include <utils.h>
#include <cub3d.h>

void		parse_sprites(char *data, t_win *win)
{
	int		i;

	i = SPR_T1;
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"S "))
	{
		while (win->tex[i].wall != NULL)
			i++;
		parse_tex(data, win, i);
	}
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SM"))
		parse_tex(data, win, SPR_M);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SI"))
		parse_tex(data, win, SPR_I);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SC"))
		parse_tex(data, win, SPR_C);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"ST"))
		parse_tex(data, win, SPR_TR);
	if (win->color.spr_i >= S_NUM)
		close_error("Too many sprites\n");
	win->color.spr_i++;
}

static int	sprite_pos(t_win *win, char *c, int *pos)
{
	int		i;

	i = 0;
	while (i < S_NUM)
	{
		if (win->type[i].c == *c)
		{
			win->spr[*pos].x = win->pos.tmp_x + .5;
			win->spr[*pos].y = win->pos.tmp_y + .5;
			win->spr[*pos].tex_id = win->type[i].tex_i;
			(*pos)++;
			*c = '0';
			return (1);
		}
		i++;
	}
	return (0);
}

static void	save_sprite(t_win *win)
{
	int 	y;
	int 	x;
	int		pos;

	pos = 0;
	y = 0;
	while (y < win->map.map_h)
	{
		x = 0;
		while (x < win->map.map_w)
		{
			if (ft_strchr(SPRITE_SET, win->map.map[y][x]))
			{
				win->pos.tmp_x = x;
				win->pos.tmp_y = y;
				if (!sprite_pos(win, &win->map.map[y][x], &pos))
					close_error("Missing texture for the sprite\n");
			}
			x++;
		}
		y++;
	}
}

static int	sprite_on(t_win *win, char c)
{
	int 	i;

	i = 0;
	while (i < S_NUM)
	{
		if (win->type[i].c == c)
			return (1);
		i++;
	}
	return (0);
}

static void	sprite_init(t_win *win)
{
	win->type[0].c = '2';
	win->type[0].tex_i = SPR_T1;
	win->type[1].c = '3';
	win->type[1].tex_i = SPR_T2;
	win->type[2].c = '4';
	win->type[2].tex_i = SPR_T3;
	win->type[3].c = 'I';
	win->type[3].tex_i = SPR_I;
	win->type[4].c = 'C';
	win->type[4].tex_i = SPR_C;
	win->type[5].c = 'T';
	win->type[5].tex_i = SPR_TR;
	win->type[6].c = 'M';
	win->type[6].tex_i = SPR_M;
}

void		sprite_set(t_win *win)
{
	int 	x;
	int		y;

	sprite_init(win);
	y = 0;
	while (y < win->map.map_h)
	{
		x = 0;
		while (x < win->map.map_w)
		{
			if (ft_strchr(SPRITE_SET, win->map.map[y][x]))
			{
				if (!sprite_on(win, win->map.map[y][x]))
					close_error("Missing sprite texture\n");
				win->spr_i++;
			}
			x++;
		}
		y++;
	}
	win->spr = ft_calloc(win->spr_i, sizeof(t_spr));
	malloc_check(win->spr);
	save_sprite(win);
}