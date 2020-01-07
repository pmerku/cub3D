/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:43:21 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:43:21 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_atoi() function is a recreation of the atoi() function included
** in "stdlib.h". This implementation does work with INT_MIN and INT_MAX
** defined in "limits.h", but it does not handle overflow.
*/

#include <libft.h>

int		ft_atoi(const char *str)
{
	int		num;
	int		prefix;

	num = 0;
	prefix = 1;
	while (*str != '\0' && (*str == '\t' || *str == '\n' || *str == '\v' ||
			*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		prefix = (*str == '-') ? -1 : 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	return (num * prefix);
}
