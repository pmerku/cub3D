/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 02:43:59 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/10 07:56:05 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static const char	*g_charset = "0123456789ABCDEF";

static int			ft_intlen_base(int n, int base)
{
	int		len;

	if (base < 2 || base > 16)
		return (0);
	len = (n <= 0);
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

char				*ft_itoa_base(int n, int base)
{
	char	*str;
	size_t	len;

	len = ft_intlen_base(n, base);
	str = (char*)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	if (n < 0 && base == 10)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	else
		n *= -1;
	str[len] = '\0';
	while (len && n)
	{
		str[len - 1] = g_charset[-(n % base)];
		n /= base;
		len--;
	}
	return (str);
}
