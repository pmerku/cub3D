/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:31:35 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/30 14:55:22 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** ---------------------------------------------------------------------------
** 							Header includes
** ---------------------------------------------------------------------------
*/

# include <cub3d.h>

/*
** ---------------------------------------------------------------------------
** 							Utils functions
** ---------------------------------------------------------------------------
*/

int		close_win(t_win *win);
int		close_key(int keycode, t_win *win);
int		close_error(char *s);
void	delete_data(char **data);

void	malloc_check(void *ptr);
void	*ft_malloc(size_t size);

#endif
