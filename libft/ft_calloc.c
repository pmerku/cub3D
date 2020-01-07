/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:43:06 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:43:06 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The function ft_calloc() is a recreation of the function calloc() included
** in "stdlib.h". The function allocates enough space for the count of objects
** with size bytes of memory and zeroes the allocated memory. It returns a
** pointer to the allocated memory.
*/

#include <stdlib.h>
#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, (count * size));
	return (mem);
}
