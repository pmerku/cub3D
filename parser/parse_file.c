/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 10:28:47 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include <fcntl.h>
#include <ft_string.h>
#include <ft_libft.h>
#include <unistd.h>
#include "utils.h"
#include "parser.h"
#include "cub3d.h"

/**
 * Helper function
 * @param s1 first string to join
 * @param s2 second string to join
 * @return joined string
 */
char	*ft_strjoin_free1(char const *s1, char const *s2) {
	if (!s1 || !s2)
		return NULL;
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *str = ft_malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return NULL;
	ft_memcpy(str, s1, len1 + 1);
	ft_memcpy(str + len1, s2, len2 + 1);
	ft_free((void*)s1);
	return str;
}

/**
 * Helper function
 * @param s1 first string to join
 * @param s2 second string to join
 * @return joined string
 */
char	*ft_strjoin_free12(char const *s1, char const *s2) {
	if (!s1 || !s2)
		return NULL;
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *str = ft_malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return NULL;
	ft_memcpy(str, s1, len1 + 1);
	ft_memcpy(str + len1, s2, len2 + 1);
	ft_free((void*)s1);
	ft_free((void*)s2);
	return str;
}

/**
 * Test if all the mandatory data is present
 * @param win global game structure
 * @return result of the tests (if not 0, then an element is missing)
 */
static int	mandatory_elements(t_win *win) {
	int res = 0;
	res += (win->x == 0);
	res += (win->y == 0);
	res += (win->tex[N_WALL].wall == NULL);
	res += (win->tex[S_WALL].wall == NULL);
	res += (win->tex[E_WALL].wall == NULL);
	res += (win->tex[W_WALL].wall == NULL);
	res += (win->color.f_color == 0xFF000000 && win->tex[FLOOR].wall == NULL);
	res += (win->color.c_color == 0xFF000000 && win->tex[CEILING].wall == NULL);
	return res == 0;
}

/**
 * Finate state machine for each element of the configuration file
 * @param data the current line in the file
 * @param win global game structure
 */
static void	parse_info(char **data, t_win *win) {
	if ((*(u_int16_t *)*data) == (*(u_int16_t *)"R "))
		parse_resolution(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t *)"F ")
		|| (*(u_int16_t *)*data) == (*(u_int16_t *)"C "))
		parse_argb(*data, &win->color);
	else if (data[0][0] == 'S' && data[0][1] != 'O')
		parse_sprites(*data, win);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t*)"NO"))
		parse_tex(*data, win, N_WALL);
	else if ((*(u_int16_t *)*data) == (*(u_int16_t*)"SO"))
		parse_tex(*data, win, S_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"WE"))
		parse_tex(*data, win, W_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"EA"))
		parse_tex(*data, win, E_WALL);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"FT"))
		parse_tex(*data, win, FLOOR);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"CT"))
		parse_tex(*data, win, CEILING);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"BD"))
		parse_tex(*data, win, DOOR);
	else if ((*(u_int16_t*)*data) == (*(u_int16_t*)"BH"))
		parse_tex(*data, win, DOOR_H);
	else if (**data != 16 && !ft_strchr(ELEM_S, **data))
		close_error("Unknown element\n");
}

/**
 * Parse a single line of the file
 * @param data file data array
 * @param win global game structure
 */
static void	parse_settings(char *data, t_win *win) {
	char	**elements = ft_split(data, '\n');
	ft_free(data);
	malloc_check(elements);
	int index = 0;
	for (; elements[index] && !ft_strchr(ELEM_S, elements[index][0]); index++)
		parse_info(&elements[index], win);
	parse_map(&elements[index], win);
	delete_data(elements);
}

/**
 * Save the file as an array
 * @param fd file file descriptor
 * @param win global game structure
 */
static void	parse_elements(int fd, t_win *win) {
	char *tmp = NULL;
	int res = 1;
	char *data = ft_strdup("");

	malloc_check(data);
	while (res > 0) {
		res = get_next_line(fd, &tmp);
		if (res < 0)
			close_error("Failed to read file\n");
		if (ft_strlen(tmp) == 0) {
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

/**
 * Parse file name, parse elements of the file, and validate the map
 * @param path path to file
 * @param win global game structure
 */
void		parse_file(char *path, t_win *win) {
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
	sprite_set(win);
	win->z_buff = ft_calloc(win->x, sizeof(double));
	malloc_check(win->z_buff);
}
