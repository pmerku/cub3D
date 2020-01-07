/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:49:22 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:49:22 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strnlen(const char *s, size_t n)
{
	size_t	len;

	len = 0;
	while (len < n)
	{
		if (!*s)
			break ;
		len++;
		s++;
	}
	return (len);
}
