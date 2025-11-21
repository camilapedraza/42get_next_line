/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/21 21:32:24 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char		stash[20000];
	char			*buffer;
	char			*newline;
	static ssize_t	count;
	char            *line;
	// could move this to new functions
	ssize_t			read_bytes;
	ssize_t			line_bytes;
	ssize_t			stash_bytes;
	
	if (fd < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	newline = NULL;
	if (count)
	{
		newline = ft_memchr(stash, '\n', count);
		if (newline)
		{
			line_bytes = (newline - stash) + 1;
			line = ft_calloc((line_bytes + 1), sizeof(char));
			if (!line)
			{
				free(buffer);
				return (NULL);
			}
			ft_memcpy(line, stash, line_bytes);
			stash_bytes = count - line_bytes;
			if (stash_bytes)
				ft_memcpy(stash, stash + line_bytes, stash_bytes);
			count = stash_bytes;
			free(buffer);
			return (line);
		}
	}
	// check read for errors or end, otherwise read and stash until newline is found!
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
	// NEW FUNCTION STARTING HERE
	line_bytes = 0;
	if (newline)
		line_bytes = (newline - buffer) + 1;
	line = ft_calloc((count + line_bytes + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	if (count > 0)
		ft_memcpy(line, stash, count);
	if (newline)
		ft_memcpy(line + count, buffer, line_bytes);
	count = read_bytes - line_bytes;
	if (count)
		ft_memcpy(stash, buffer + line_bytes, count);
	free(buffer);
	return (line);
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
