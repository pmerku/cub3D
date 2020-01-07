/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:47:03 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:47:03 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	if (dstsize < dlen)
		slen = slen + dstsize;
	else
		slen = slen + dlen;
	i = 0;
	while (src[i] != '\0' && dlen < dstsize - 1 && dst != src)
	{
		dst[dlen] = src[i];
		i++;
		dlen++;
	}
	if (dlen <= dstsize)
		dst[dlen] = '\0';
	return (slen);
}
