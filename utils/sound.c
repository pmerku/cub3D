/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:19:04 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/18 12:16:04 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

void	sound_effect(char *path)
{
	char	*cmd;
	int		i;

	i = fork();
	if (i < 0)
		close_error("Sound error\n");
	else if (i == 0)
	{
		cmd = ft_strjoin("afplay ", path);
		malloc_check(cmd);
		system(cmd);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
}

void	sound_stop(void)
{
	int		i;

	i = fork();
	if (i < 0)
		close_error("Sound error\n");
	else if (i == 0)
	{
		system("killall afplay");
		exit(EXIT_SUCCESS);
	}
}
