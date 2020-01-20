/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:46:43 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/17 10:51:50 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*mem;

	len = ft_strlen(s1);
	mem = (char*)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s1, len + 1);
	return (mem);
}
