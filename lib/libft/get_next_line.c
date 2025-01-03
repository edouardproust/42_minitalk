/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:15:14 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 17:50:15 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_stash(char **stash, int fd)
{
	char	*buffer;
	int		br;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_ptrs(1, stash));
	buffer[0] = '\0';
	br = 1;
	while (!ft_strchr(buffer, '\n') && br != 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0)
			return (free_ptrs(2, &buffer, stash));
		if (br > 0)
		{
			buffer[br] = '\0';
			*stash = ft_strjoin(*stash, buffer);
			if (!*stash)
				return (free_ptrs(1, &buffer));
		}
	}
	free_ptrs(1, &buffer);
	return (*stash);
}

static char	*set_line(char **stash)
{
	char	*line;
	int		i;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i] == '\0' && i > 0)
		i--;
	line = ft_substr(*stash, 0, i + 1);
	if (!line)
		return (free_ptrs(1, stash));
	if (ft_strlen(line) == 0)
		return (free_ptrs(2, &line, stash));
	return (line);
}

static char	*update_stash(int line_len, char **stash)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*stash);
	if (len == line_len)
		return (free_ptrs(1, stash));
	tmp = ft_substr(*stash, line_len, len);
	free_ptrs(1, stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = fill_stash(&stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = set_line(&stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = update_stash(ft_strlen(line), &stash[fd]);
	return (line);
}
