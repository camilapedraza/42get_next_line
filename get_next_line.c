/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:24:57 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/25 16:53:31 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

static void	update_stash(char **stash)
{
	char	*updated_stash;
	size_t	i;

	if (!stash || !*stash)
		return;
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	updated_stash = ft_strdup((*stash) + i);
	free(*stash);
	*stash = updated_stash;
}

static char	*build_line(char *stash)
{
	char *line;
	size_t len;
	size_t i;

	if (!stash || !*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	fill_stash(int fd, char **stash, char **buffer)
{
	char	*updated_stash;
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0 && !ft_strchr(*stash, '\n'))
	{
		bytes = read(fd, *buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (-1);
		(*buffer)[bytes] = '\0';
		updated_stash = ft_strjoin(*stash, *buffer);
		if (!updated_stash)
			return (-1);
		free(*stash);
		*stash = updated_stash;
	}
	return (0);
}

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char *stash;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fill_stash(fd, &stash, &buffer) < 0)
	{
		free(buffer);
		return (NULL);
	}
	line = build_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		free(buffer);
		return (NULL);
	}
	update_stash(&stash);
	free(buffer);
	return (line);
}
