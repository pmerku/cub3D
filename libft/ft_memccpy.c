/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:44:45 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:44:45 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (n)
	{
		d = (unsigned char*)dst;
		s = (const unsigned char*)src;
		while (n != 0)
		{
			*d = *s;
			if (*d == (unsigned char)c)
				return (d + 1);
			d++;
			s++;
			n--;
		}
	}
	return (NULL);
}
