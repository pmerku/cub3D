/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:28:51 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 10:07:46 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** ---------------------------------------------------------------------------
** 							Header includes
** ---------------------------------------------------------------------------
*/

# include <cub3d.h>

/*
** ---------------------------------------------------------------------------
** 							Parser functions
** ---------------------------------------------------------------------------
*/

void	parse_file(char *path, t_win *win);
void	parse_resolution(char *data, t_win *win);
void	parse_argb(char *data, t_win *win);
void	parse_tex(char *data, t_win *win, int i);

void	parse_map(char **data, t_win *win);
void	map_validate(t_win *win);

#endif
