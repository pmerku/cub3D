/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 11:38:58 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <parser.h>
#include <cub3d.h>

static void	parse_info(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'R')
		parse_resolution(data, win, i);
	else if (data[*i][0] == 'S')
		parse_sprite();
	else
		parse_texture(data, win, i);
}

void		parse_file(char *s, t_win *win)
{
	char	**data;
	char	*ptr;
	int		fd;
	int		i;

	ptr = ft_strrchr(s, '.');
	if (!ptr || ft_strncmp(ptr, ".cub", 4) != 0)
		close_error(0);
	fd = open(s, O_RDONLY);
	data = save_data(fd);
	i = 0;
	while (data[i])
	{
		if (data[i][0] != '1' && data[i])
			parse_info(data, win, &i);
		else
			parse_map(data, &win->map, &i);
		if (!data[i])
			break ;
		i++;
	}
	close(fd);
	delete_data(data);
}
