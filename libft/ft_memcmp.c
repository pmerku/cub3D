/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:44:59 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:44:59 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_memcmp(const	void *s1, const	void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;

	if (n == 0)
		return (0);
	src1 = (unsigned char*)s1;
	src2 = (unsigned char*)s2;
	while (n)
	{
		if (*src1 != *src2)
			return (*src1 - *src2);
		src1++;
		src2++;
		n--;
	}
	return (0);
}
