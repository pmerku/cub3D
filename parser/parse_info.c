/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/03/06 09:48:26 by prmerku       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include <ft_string.h>
#include <ft_ctype.h>
#include <ft_libft.h>
#include <ft_stdlib.h>
#include <mlx.h>
#include "utils.h"
#include <stdio.h>

/**
 * Check if values are correct
 * @param s data to parse
 */
static void	split_check(char *s) {
	if (!s)
		close_error("Incorrect values\n");
	for (int i = ft_strlen(s); i >= 0; i--) {
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\0')
			close_error("Incorrect values\n");
	}
}

/**
 * Parse resolution
 * @param data data to parse
 * @param win global window structure
 */
void		parse_resolution(char *data, t_win *win) {
	int		h;
	int		w;

	mlx_get_screen_size(win->mlx, &w, &h);
	if (win->x >= 1 && win->x <= w && win->y >= 1 && win->y <= h)
		close_error("Duplicate resolution\n");
	char **s = ft_split(data, ' ');
	malloc_check(s);
	split_check(s[1]);
	split_check(s[2]);
	if (s[3] != NULL)
		close_error("Incorrect values, too many numbers\n");
	win->x = (s[1] == NULL) ? close_error("Incorrect values resolution x\n") : ft_atoi(s[1]);
	win->y = (s[2] == NULL) ? close_error("Incorrect values resolution y\n") : ft_atoi(s[2]);
	if (win->x == 0 || win->y == 0)
		close_error("Invalid resolution\n");
	if (win->x > 16384 || win->y > 16384)
		close_error("Value is over the limit\n");
	win->x = (win->x > w && (!win->save || win->x > 16384)) ? w : win->x;
	win->y = (win->y > h && (!win->save || win->y > 16384)) ? h - 45 : win->y;
	win->x = (win->x < 1) ? close_error("Incorrect values resolution x (2)\n") : win->x;
	win->y = (win->y < 1) ? close_error("Incorrect values resolution y (2)\n") : win->y;
	delete_data(s);
}

/**
 * Parse the texture data
 * @param data path to texture
 * @param win global game structure
 * @param i texture id
 */
void		parse_tex(char *data, t_win *win, int i) {
	if (win->tex[i].wall)
		close_error("Duplicate texture\n");
	data += 3;
	while (*data && (*data == ' '))
		data++;
	char *path = ft_strdup(data);
	malloc_check(path);
	win->tex[i].wall = mlx_xpm_file_to_image(win->mlx, path, &win->tex[i].tex_w, &win->tex[i].tex_h);
	if (!win->tex[i].wall)
		close_error("Invalid texture\n");
	win->tex[i].data = mlx_get_data_addr(win->tex[i].wall, &win->tex[i].bpp, &win->tex[i].line_len, &win->tex[i].endian);
	if (!win->tex[i].data)
		close_error("Couldn't get texture data\n");
	ft_free(path);
}

/**
 * Finate state machine for sprites data
 * @param data current line in file
 * @param win global game structure
 */
void		parse_sprites(char *data, t_win *win) {
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"S "))
		parse_tex(data - 1, win, SPR_T2);
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"S2"))
		parse_tex(data, win, SPR_T3);
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"S3"))
		parse_tex(data, win, SPR_T4);
	if ((*(u_int16_t *)data) == (*(u_int16_t *)"SL"))
		parse_tex(data, win, SPR_T1);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SM"))
		parse_tex(data, win, SPR_M);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SI"))
		parse_tex(data, win, SPR_I);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"SP"))
		parse_tex(data, win, SPR_P);
	else if ((*(u_int16_t *)data) == (*(u_int16_t *)"ST"))
		parse_tex(data, win, SPR_TR);
	if (win->color.spr_i >= S_NUM)
		close_error("Too many sprites\n");
	win->color.spr_i++;
}
