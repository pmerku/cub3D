/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/30 13:22:39 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <parser.h>
#include <cub3d.h>

static int	mandatory_elements(t_win *win)
{
	int		res;

	res = 0;
	res += (win->x == 0);
	res += (win->y == 0);
	res += (win->tex[N_WALL].wall == NULL);
	res += (win->tex[S_WALL].wall == NULL);
	res += (win->tex[E_WALL].wall == NULL);
	res += (win->tex[W_WALL].wall == NULL);
	// TODO: sprites parsing
	//res += (win->map.sprite == NULL);
	res += (win->color.f_color == 0xFF000000);
	res += (win->color.c_color == 0xFF000000);
	return (res == 0);
}

/*
** Parse the 2D array and depending on position parse with correct function
**
** @param  char  **data allocated 2D array to parse
** @param  t_win   *win allocated global window structure
** @param  int    index reference to index position
** @return void
*/

static void	parse_info(char **data, t_win *win)
{
	if ((*(u_int16_t *)*data) == (*(u_int16_t *)"R "))
		parse_resolution(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"S "))
		parse_sprite();
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"F ")
		|| (*(u_int16_t *)*data) == (*(u_int16_t *)"C "))
		parse_argb(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"NO"))
		parse_w(*data, win, N_WALL);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"SO"))
		parse_w(*data, win, S_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"WE"))
		parse_w(*data, win, W_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"EA"))
		parse_w(*data, win, E_WALL);
	else if (**data != '1' && **data != 16)
		close_error("Unknown element\n");
}

static void	parse_settings(char *data, t_win *win)
{
	int		index;
	char	**elements;

	elements = ft_split(data, '\n');
	free(data);
	malloc_check(elements);
	index = 0;
	while (elements[index] && elements[index][0] != '1')
	{
		parse_info(&elements[index], win);
		index++;
	}
	parse_map(&elements[index], win);
	delete_data(elements);
}

static void	parse_elements(int fd, t_win *win)
{
	char	*data;
	char	*tmp;
	int		res;

	res = 1;
	data = ft_strdup("");
	malloc_check(data);
	while (res > 0)
	{
		res = get_next_line(fd, &tmp);
		if (res < 0)
			close_error("Failed to read file\n");
		if (ft_strlen(tmp) == 0)
		{
			tmp = ft_strjoin_free1(tmp, "\n");
			malloc_check(tmp);
			*tmp = 16;
		}
		tmp = ft_strjoin_free1(tmp, "\n");
		malloc_check(tmp);
		data = ft_strjoin_free12(data, tmp);
		malloc_check(data);
	}
	parse_settings(data, win);
}

void		parse_file(char *path, t_win *win)
{
	char	*ptr;
	int		fd;

	ptr = ft_strrchr(path, '.');
	if (!ptr || ft_strncmp(ptr, ".cub", 4) != 0)
		close_error("Invalid file\n");
	fd = open(path, O_RDONLY);
	parse_elements(fd, win);
	close(fd);
	if (!mandatory_elements(win))
		close_error("Missing elements\n");
	map_validate(win);
	if (win->pos.x == 0 || win->pos.y == 0)
		close_error("No spawn point\n");
}
