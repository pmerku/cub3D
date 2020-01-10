/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:46:33 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:46:33 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static size_t	ft_strnum(const char *s, char c)
{
	const char	*ptr;
	int			i;

	i = 0;
	ptr = s;
	if (c == '\0')
		return (0);
	while (ptr)
	{
		ptr++;
		i++;
		ptr = ft_strchr(ptr, c);
	}
	return (i);
}

static size_t	ft_strhlen(const char *s, char c)
{
	int		i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static void		*ft_free(char **str, size_t i)
{
	while (i != 0)
	{
		i--;
		free(&str[i]);
	}
	free(str);
	return (NULL);
}

static char		**ft_str_arr(char **str, const char *s, char c)
{
	size_t	i;
	size_t	slen;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			continue ;
		slen = ft_strhlen(s, c);
		str[i] = (char*)malloc(sizeof(char) * (slen + 1));
		if (!str[i])
			return (ft_free(str, i));
		if (*s && *s != c)
		{
			ft_strlcpy(str[i], s, slen + 1);
			s += slen;
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

char			**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (ft_strnum(s, c) + 1));
	if (!str)
		return (NULL);
	str = ft_str_arr(str, s, c);
	if (str == NULL)
		return (NULL);
	return (str);
}
