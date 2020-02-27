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

#include <libft.h>
#include <utils.h>

/*
** Check if color input is correct
**
** @param  char *data passed string from 2D array
** @return int      i number of commas
*/

static void	comma_check(char **s)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j] == ' ')
			j++;
		while (ft_isdigit(s[i][j]))
			j++;
		while (s[i][j] == ' ')
			j++;
		if (s[i][j] != '\0' && s[i][j] != ',')
			close_error("Incorrect values\n");
		i++;
	}
}

/*
** Split colors
**
** @param  char *data passed string from 2D array
** @return char    ** splitted array
*/

static char	**color_split(char *data)
{
	char	**s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (data[j])
	{
		if (data[j] == ',')
			i++;
		j++;
	}
	if (i != 2)
		close_error("Incorrect values\n");
	s = ft_split(data + 1, ',');
	malloc_check(s);
	return (s);
}

/*
** Parse the 2D array and save the colors separately in the global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win allocated global window structure
** @return void
*/

void		parse_argb(char *data, t_color *c)
{
	char	**s;

	s = color_split(data);
	comma_check(s);
	c->r = (s[0] == NULL) ? close_error("Incorrect values\n") : ft_atoi(s[0]);
	c->g = (s[1] == NULL) ? close_error("Incorrect values\n") : ft_atoi(s[1]);
	c->b = (s[2] == NULL) ? close_error("Incorrect values\n") : ft_atoi(s[2]);
	if (c->r > 255 || c->g > 255 || c->b > 255)
		close_error("Incorrect ARGB numbers\n");
	if (*data == 'F')
	{
		if (c->c_on & F_COLOR)
			close_error("Duplicate color\n");
		c->f_color = c->a << 24 | c->r << 16 | c->g << 8 | c->b;
	}
	if (*data == 'C')
	{
		if (c->c_on & C_COLOR)
			close_error("Duplicate color\n");
		c->c_color = c->a << 24 | c->r << 16 | c->g << 8 | c->b;
	}
	delete_data(s);
	c->c_on |= (*data == 'F') ? F_COLOR : C_COLOR;
}
