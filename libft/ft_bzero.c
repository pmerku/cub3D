/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:43:15 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:43:15 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The function ft_bzero() is a recreation of the function bzero() included
** in "strings.h". This implementation work by calling the function ft_memset()
** that zeroes out n bytes to the string s. If n is 0 ft_bzero does nothing.
*/

#include <libft.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
