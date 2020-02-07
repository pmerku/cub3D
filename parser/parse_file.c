/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/07 11:47:01 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <parser.h>
#include <cub3d.h>

/*
** Check if all mandatory elements in '.cub' file are present
**
** @param  t_win *win allocated global window structure
** @return int        status code 0 if all elements are present
*/

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
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"F ")
		|| (*(u_int16_t *)*data) == (*(u_int16_t *)"C "))
		parse_argb(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"S ")
		|| (*(u_int16_t *)*data) == (*(u_int16_t *)"ST")
		|| (*(u_int16_t *)*data) == (*(u_int16_t *)"SI"))
		parse_sprites(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"NO"))
		parse_tex(*data, win, N_WALL);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"SO"))
		parse_tex(*data, win, S_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"WE"))
		parse_tex(*data, win, W_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"EA"))
		parse_tex(*data, win, E_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"FT"))
		parse_tex(*data, win, FLOOR);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"CT"))
		parse_tex(*data, win, CEILING);
	else if (**data != '1' && **data != 16)
		close_error("Unknown element\n");
}

/*
** Parse array by splitting it into a 2D array and parse each line
**
** @param  char  *data saved array
** @param  t_win  *win allocated global window structure
** @return void
*/

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

/*
** Read the file and save it in an array
**
** @param  int     fd file descriptor index
** @param  t_win *win allocated global window structure
** @return void
*/

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

/*
** Parse file name, parse the elements of the file and validate the map
**
** @param  char  *path path to file name
** @param  t_win  *win allocated global window structure
** @return void
*/

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
