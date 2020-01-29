/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:36:22 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/29 09:25:52 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

void		*ft_malloc(size_t size)
{
	void	*mem;

	mem = NULL;
	if (size > 0)
		mem = malloc(size);
	if (!mem)
		close_error("Malloc fail\n");
	return (mem);
}

void		malloc_check(void *ptr)
{
	if (!ptr)
		close_error("Malloc fail\n");
}

/*
** Delete 2D array and its indexes
**
** @param  char ** allocated 2D array
** @return void
*/

void		delete_data(char **data)
{
	int		i;

	i = 0;
	while (data[i] != NULL)
	{
		free(data[i]);
		i++;
	}
	free(data);
}
