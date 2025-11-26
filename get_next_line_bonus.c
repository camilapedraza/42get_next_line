/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:24:57 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/26 16:24:32 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clean_stash(char **stash)
{
	if (*stash)
		free(*stash);
	*stash = NULL;
}

static void	update_stash(char **stash)
{
	char	*updated_stash;
	size_t	i;

	if (!stash || !*stash)
		return ;
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
	char	*line;
	size_t	len;
	size_t	i;

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

char	*get_next_line(int fd)
{
	static char	*stash[__SHRT_MAX__];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd > __SHRT_MAX__ || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (clean_stash(&stash[fd]), NULL);
	if (fill_stash(fd, &stash[fd], &buffer) < 0)
		return (clean_stash(&stash[fd]), free(buffer), NULL);
	line = build_line(stash[fd]);
	if (!line)
		return (clean_stash(&stash[fd]), free(buffer), NULL);
	update_stash(&stash[fd]);
	free(buffer);
	return (line);
}
