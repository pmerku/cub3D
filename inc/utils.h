/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:31:35 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 11:37:24 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <cub3d.h>

int		close_win(t_win *win);
int		close_key(int keycode, t_win *win);
int		close_error(int i);

void	delete_data(char **data);
char	**save_data(int fd);

#endif
