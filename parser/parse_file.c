/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 10:21:02 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <parser.h>
#include <cub3d.h>

/*
** Parse the 2D array and depending on position parse with correct function
**
** @param  char  **data allocated 2D array to parse
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

static void	parse_info(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'R')
		parse_resolution(data, win, i);
	else if (data[*i][0] == 'S')
		parse_sprite();
	else
		parse_texture(data, win, i);
}

/*
** Parse the file and save the lines separately in a 2D array to parse
**
** @param  char  *s   path to file
** @param  t_win *win allocated global window structure
** @param  int   *i   reference to index position
** @return void
*/

void		parse_file(char *s, t_win *win)
{
	char	**data;
	char	*ptr;
	int		fd;
	int		i;

	ptr = ft_strrchr(s, '.');
	if (!ptr || ft_strncmp(ptr, ".cub", 4) != 0)
		close_error("Invalid file\n");
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
