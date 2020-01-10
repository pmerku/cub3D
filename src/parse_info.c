/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/10 13:47:19 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

void		parse_resolution(char **data, t_win *win, int *i)
{
	char	**s;

	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error(2);
	win->win_x = ft_atoi(s[1]);
	win->win_y = ft_atoi(s[2]);
	delete_data(s);
}

void		parse_sprite(void)
{
}

static void	parse_trgb(char **data, t_win *win, int *i)
{
	int		j;
	char	**s;

	j = 0;
	while (data[*i][j])
	{
		if (data[*i][j] == ',')
			data[*i][j] = ' ';
		j++;
	}
	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error(2);
	win->tex.r = ft_atoi(s[1]);
	win->tex.g = ft_atoi(s[2]);
	win->tex.b = ft_atoi(s[3]);
	win->tex.t = 0;
	if ((win->tex.r > 255 || win->tex.g > 255 || win->tex.b > 255) &&
			(win->tex.r < 0 || win->tex.g < 0 || win->tex.b < 0))
		close_error(2);
	if (data[*i][0] == 'F')
		win->tex.f_color = win->tex.t << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	if (data[*i][0] == 'C')
		win->tex.c_color = win->tex.t << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	delete_data(s);
}

void		parse_texture(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'F' || data[*i][0] == 'C')
		parse_trgb(data, win, i);
}
