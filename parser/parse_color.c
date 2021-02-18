/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 11:37:42 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ctype.h>
#include <ft_libft.h>
#include <ft_stdlib.h>
#include "utils.h"

/**
 * Split the RGB values
 * @param data the color value to split
 * @return splitted color values
 */
static char	**color_split(char *data) {
	int	i = 0;
	for (int j = 0; data[j]; j++) {
		if (data[j] == ',')
			i++;
	}
	if (i != 2)
		close_error("Incorrect values color_split\n");
	char **s = ft_split(data + 1, ',');
	malloc_check(s);
	return s;
}

/**
 * Parse each color value and save it
 * @param data values to parse
 * @param c color structure
 */
void		parse_argb(char *data, t_color *c) {
	char **s = color_split(data);
	for (int i = 0; s[i]; i++) {
		int j = 0;
		while (s[i][j] == ' ')
			j++;
		while (ft_isdigit(s[i][j]))
			j++;
		while (s[i][j] == ' ')
			j++;
		if (s[i][j] != '\0' && s[i][j] != ',')
			close_error("Incorrect values argb\n");
	}
	c->r = (s[0] == NULL) ? close_error("Incorrect values r\n") : ft_atoi(s[0]);
	c->g = (s[1] == NULL) ? close_error("Incorrect values g\n") : ft_atoi(s[1]);
	c->b = (s[2] == NULL) ? close_error("Incorrect values b\n") : ft_atoi(s[2]);
	if (c->r > 255 || c->g > 255 || c->b > 255)
		close_error("Incorrect ARGB numbers\n");
	if (*data == 'F') {
		if (c->c_on & F_COLOR)
			close_error("Duplicate color floor\n");
		c->f_color = c->a << 24 | c->r << 16 | c->g << 8 | c->b;
	}
	if (*data == 'C') {
		if (c->c_on & C_COLOR)
			close_error("Duplicate color ceiling\n");
		c->c_color = c->a << 24 | c->r << 16 | c->g << 8 | c->b;
	}
	delete_data(s);
	c->c_on |= (*data == 'F') ? F_COLOR : C_COLOR;
}
