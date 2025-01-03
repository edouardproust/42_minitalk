/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:31:01 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 17:56:53 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees a 2D array of pointers (e.g. an array of strings char**).
 * The array must be NULL-terminated.
 */
void	free_matrix(void ***array)
{
	if (!array || !*array)
		return ;
	while (*array)
	{
		free(**array);
		**array = NULL;
		(*array)++;
	}
	free(*array);
	*array = NULL;
}
