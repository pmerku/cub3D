/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:28:51 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 11:41:26 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <cub3d.h>

void	parse_file(char *s, t_win *win);
void	parse_resolution(char **data, t_win *win, int *i);
void	parse_sprite(void);
void	parse_texture(char **data, t_win *win, int *i);
void	parse_map(char **data, t_map *map, int *i);

#endif
