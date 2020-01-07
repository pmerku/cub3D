/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:49:39 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:49:39 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const	char *needle, size_t len)
{
	size_t	pos;
	size_t	nlen;

	pos = 0;
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char*)haystack);
	while (haystack[pos] != '\0')
	{
		if (pos + nlen > len)
			return (NULL);
		if (ft_strncmp(haystack + pos, needle, nlen) == 0)
			return ((char*)haystack + pos);
		pos++;
	}
	return (NULL);
}
