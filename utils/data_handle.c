/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:36:22 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/29 09:25:52 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_memory.h>
#include "utils.h"

/**
 * Test for allocation failure
 * @param ptr pointer to memory to test
 */
void		malloc_check(void *ptr) {
	if (!ptr)
		close_error("Malloc fail\n");
}

/**
 * Free 2D array
 * @param data array to free
 */
void		delete_data(char **data) {
	for (int i = 0; data[i] != NULL; i++)
		ft_free(data[i]);
	ft_free(data);
}
