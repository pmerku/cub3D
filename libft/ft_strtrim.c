/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:49:58 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:49:58 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static size_t	ft_find_start(const char *s1, const char *set)
{
	size_t	pos;

	pos = 0;
	while (s1[pos] != '\0' && ft_strchr(set, s1[pos]))
		pos++;
	return (pos);
}

static size_t	ft_find_end(const char *s1, const char *set)
{
	size_t	pos;

	pos = ft_strlen(s1);
	while (ft_strchr(set, s1[pos]) && pos)
		pos--;
	return (pos);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	pos_1;
	size_t	pos_2;

	if (!s1 || !set)
		return (NULL);
	pos_1 = ft_find_start(s1, set);
	pos_2 = ft_find_end(s1, set);
	len = pos_2 - pos_1 + 1;
	if (pos_2 < pos_1)
		len = 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + pos_1, len + 1);
	return (str);
}
