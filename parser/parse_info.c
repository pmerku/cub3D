/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 07:57:31 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

void		parse_resolution(char **data, t_win *win, int *i)
{
	char	**s;

	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error(2);
	win->x = ft_atoi(s[1]);
	win->y = ft_atoi(s[2]);
	delete_data(s);
}

void		parse_sprite(void)
{
}

static void	parse_argb(char **data, t_win *win, int *i)
{
	char	**s;

	while (ft_strchr(data[*i], ','))
		(*(char *)ft_strchr(data[*i], ',')) = ' ';
	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error(2);
	win->tex.r = ft_atoi(s[1]);
	win->tex.g = ft_atoi(s[2]);
	win->tex.b = ft_atoi(s[3]);
	win->tex.a = 0;
	if (win->tex.r > 255 || win->tex.g > 255 || win->tex.b > 255)
		close_error(2);
	if (data[*i][0] == 'F')
		win->tex.f_color = win->tex.a << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	if (data[*i][0] == 'C')
		win->tex.c_color = win->tex.a << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	delete_data(s);
}

void		parse_texture(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'F' || data[*i][0] == 'C')
		parse_argb(data, win, i);
}
