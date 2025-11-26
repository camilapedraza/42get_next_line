/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/26 12:45:43 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*build_from_stash(char *stash, ssize_t *ct, char *buf, char *nl)
{
	char	*line;
	ssize_t	line_bytes;
	ssize_t	stash_bytes;

	line_bytes = (nl - stash) + 1;
	line = ft_calloc((line_bytes + 1), sizeof(char));
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	ft_memcpy(line, stash, line_bytes);
	stash_bytes = *ct - line_bytes;
	if (stash_bytes)
		ft_memcpy(stash, stash + line_bytes, stash_bytes);
	*ct = stash_bytes;
	free(buf);
	return (line);
}

ssize_t	read_file(int fd, char *stash, ssize_t *count, char *buffer)
{
	char	*newline;
	ssize_t	read_bytes;

	newline = NULL;
	while (!newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && *count == 0))
		{
			*count = 0;
			free(buffer);
			return (-1);
		}
		if (read_bytes == 0)
			return (0);
		newline = ft_memchr(buffer, '\n', read_bytes);
		if (!newline)
		{
			ft_memcpy(stash + *count, buffer, read_bytes);
			*count += read_bytes;
		}
	}
	return (read_bytes);
}

static char	*build_from_read(char *stash, ssize_t *ct, char *buf, ssize_t rb)
{
	char	*line;
	char	*newline;
	ssize_t	line_bytes;

	line_bytes = 0;
	newline = ft_memchr(buf, '\n', rb);
	if (newline)
		line_bytes = (newline - buf) + 1;
	line = ft_calloc((size_t)(*ct + line_bytes + 1), sizeof(char));
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	if (*ct > 0)
		ft_memcpy(line, stash, (size_t)(*ct));
	if (newline)
		ft_memcpy(line + *ct, buf, (size_t)line_bytes);
	*ct = rb - line_bytes;
	if (*ct)
		ft_memcpy(stash, buf + line_bytes, (size_t)(*ct));
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		stash[STASH_SIZE];
	static ssize_t	count;
	char			*buffer;
	char			*newline;
	ssize_t			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	newline = NULL;
	if (count)
	{
		newline = ft_memchr(stash, '\n', count);
		if (newline)
			return (build_from_stash(stash, &count, buffer, newline));
	}
	read_bytes = read_file(fd, stash, &count, buffer);
	if (read_bytes == -1)
		return (NULL);
	return (build_from_read(stash, &count, buffer, read_bytes));
}
/*
#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
    int file;
	char	*read_line;

    if (ac == 2)
    {
        file = open(av[1], O_RDONLY);
        if (file == -1)
            write(STDERR_FILENO, "Cannot read file.\n", 18);
        else
        {
            while (1) 
			{
				read_line = get_next_line(file);
				if (read_line)
					printf("%s\n", read_line);
				else
				{
					close(file);
					break ;
				}
			}
			return (0);
        }
    }
    else if (ac < 2)
        write(STDERR_FILENO, "File name missing.\n", 19);
    else
        write(STDERR_FILENO, "Too many arguments.\n", 20);
    return (1);
}*/
