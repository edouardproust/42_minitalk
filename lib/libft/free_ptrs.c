/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ptrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:54:41 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 17:51:48 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_ptrs(int count, ...)
{
	va_list	args;
	void	**ptr;
	int		i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(args, void **);
		if (ptr && *ptr)
		{
			free(*ptr);
			*ptr = NULL;
		}
		i++;
	}
	va_end(args);
	return (NULL);
}

/*
int main()
{
    char	*test;

    test = ft_strdup("Hello");
	if (!test)
        return (1);
    printf("Before free: %s\n", test);
    free_ptrs_generic(1, &test);
    printf("After free: %s\n", test);
    return (0);
}
*/
