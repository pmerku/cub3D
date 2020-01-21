/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:27:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 11:27:59 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

void	parse_map(char **data, t_map *map, int *i)
{
	int		len;

	len = 0;
	while (data[*i + len])
		len++;
	map->map_h = len;
	map->map_w = ft_strlen(data[*i]);
	map->map = (char**)malloc(sizeof(char*) * (len + 1));
	if (!map->map)
		close_error(2);
	map->map[len] = NULL;
	len = 0;
	while (data[*i] && data[*i][0] == '1')
	{
		map->map[len] = ft_strdup(data[*i]);
		if (!map->map[len])
			close_error(2);
		(*i)++;
		len++;
	}
}
