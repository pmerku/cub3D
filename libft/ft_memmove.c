/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:45:14 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:45:14 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*d_end;
	char	*s;
	char	*s_end;

	d = (char*)dst;
	s = (char*)src;
	if (!d && !s)
		return (NULL);
	if (d < s)
		ft_memcpy(dst, src, len);
	else
	{
		d_end = d + (len - 1);
		s_end = s + (len - 1);
		while (len)
		{
			*d_end = *s_end;
			d_end--;
			s_end--;
			len--;
		}
	}
	return (dst);
}
