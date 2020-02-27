/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 11:37:42 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <mlx.h>
#include <utils.h>

/*
** Parse the 2D array and save the resolution separately in the
** global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win   allocated global window structure
** @return void
*/

void		parse_resolution(char *data, t_win *win)
{
	char	**s;
	int		h;
	int		w;

	mlx_get_screen_size(win->mlx, &w, &h);
	if (win->x >= 20 && win->x <= w && win->y >= 20 && win->y <= h)
		close_error("Duplicate resolution\n");
	s = ft_split(data, ' ');
	malloc_check(s);
	win->x = (s[1] == NULL) ? close_error("Incorrect values\n") : ft_atoi(s[1]);
	win->y = (s[2] == NULL) ? close_error("Incorrect values\n") : ft_atoi(s[2]);
	if (win->x == 0 || win->y == 0)
		close_error("Invalid resolution\n");
	win->x = (win->x > w && (!win->save || win->x > 16384)) ? w : win->x;
	win->y = (win->y > h && (!win->save || win->y > 16384)) ? h - 45 : win->y;
	win->x = (win->x < 20) ? 20 : win->x;
	win->y = (win->y < 20) ? 20 : win->y;
	delete_data(s);
}

/*
** Parse the 2D array and save the textures separately in the
** global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win allocated global window structure
** @param  int       i reference to index position for textures
** @return void
*/

void		parse_tex(char *data, t_win *win, int i)
{
	char	*path;

	if (win->tex[i].wall)
		close_error("Duplicate texture\n");
	data += 3;
	while (*data && (*data == ' '))
		data++;
	path = ft_strdup(data);
	malloc_check(path);
	win->tex[i].wall = mlx_xpm_file_to_image(win->mlx, path,
			&win->tex[i].tex_w, &win->tex[i].tex_h);
	if (!win->tex[i].wall)
		close_error("Invalid texture\n");
	win->tex[i].data = mlx_get_data_addr(win->tex[i].wall,
			&win->tex[i].bpp, &win->tex[i].line_len, &win->tex[i].endian);
	if (!win->tex[i].data)
		close_error("Couldn't get texture data\n");
	free(path);
}

/*
** Parse the 2D array and save the sprites separately in the
** global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win allocated global window structure
** @return void
*/

void		parse_sprites(char *data, t_win *win)
{
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
