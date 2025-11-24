/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/24 23:01:53 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char *assemble_from_stash(char *stash, ssize_t *count, char *buffer, char *newline)
{
	ssize_t line_bytes;
	ssize_t stash_bytes;
	char *line;
	
	line_bytes = (newline - stash) + 1;
	line = ft_calloc((line_bytes + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	ft_memcpy(line, stash, line_bytes);
	stash_bytes = *count - line_bytes;
	if (stash_bytes)
		ft_memcpy(stash, stash + line_bytes, stash_bytes);
	*count = stash_bytes;
	free(buffer);
	return (line);
}

static char *assemble_from_read(char *stash, ssize_t *count, char *buffer, ssize_t read_bytes)
{
	ssize_t line_bytes;
	char *line;
	char *newline;

	line_bytes = 0;
	newline = ft_memchr(buffer, '\n', read_bytes);
	if (newline)
		line_bytes = (newline - buffer) + 1;
	line = ft_calloc((size_t)(*count + line_bytes + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	if (*count > 0)
		ft_memcpy(line, stash, (size_t)*count);
	if (newline)
		ft_memcpy(line + *count, buffer, (size_t)line_bytes);
	*count = read_bytes - line_bytes;
	if (*count)
		ft_memcpy(stash, buffer + line_bytes, (size_t)*count);
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char 	stash[STASH_SIZE];
	static ssize_t	count;
	char			*buffer;
	char			*newline;
	ssize_t			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	if (count)
	{
		newline = ft_memchr(stash, '\n', count);
		if (newline)
			return(assemble_from_stash(stash, &count, buffer, newline));
	}

	while (!newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || (read_bytes == 0 && count == 0))
		{
			count = 0;
			free(buffer);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		newline = ft_memchr(buffer, '\n', read_bytes);
		if (!newline)
		{
			ft_memcpy(stash + count, buffer, read_bytes);
			count += read_bytes;
		}
	}
	return (assemble_from_read(stash, &count, buffer, read_bytes));
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
