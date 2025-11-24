/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:32 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/24 22:11:14 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"

#include <stdio.h>

void	set_stash(struct s_stash *stash, ssize_t bytes)
{
	stash->buffer_pos = stash->buffer;
	stash->buffer_size = bytes;
}

ssize_t	read_file(int fd, struct s_stash *stash)
{
	ssize_t	read_bytes;

	read_bytes = read(fd, stash->buffer, BUFFER_SIZE);
	if (read_bytes == - 1)
		return (read_bytes);
	set_stash(stash, read_bytes);
	return (read_bytes);
}

char *move_stash_to_line(char *orig, struct s_stash *stash, size_t line_size)
{
	char	*dest;
	size_t	orig_len;
	size_t	i;

	orig_len = 0;
	if (orig)
		orig_len = ft_strlen(orig);
	dest = ft_calloc((orig_len + line_size + 1), sizeof(char));
	if (!dest)
	{
		free(orig);
		return (NULL);
	}
	if (orig_len)
		ft_memcpy(dest, orig, orig_len);
	i = orig_len;
	while (i < line_size)
		dest[i++] = *(stash->buffer_pos++);
	free(orig);
	return (dest);
}

char	*build_line(int fd, struct s_stash *stash, char *line)
{
	char	*newline;
	ssize_t	line_size;
	ssize_t	read_bytes;

	while (1)
	{
		if (stash->buffer_size > 0)
		{
			newline = ft_memchr(stash->buffer_pos, '\n', stash->buffer_size);
			if (newline)
			{
				line_size = (newline - stash->buffer_pos) + 1;
				stash->buffer_size -= line_size;
				return(move_stash_to_line(line, stash, (size_t)line_size));
			}
			line = move_stash_to_line(line, stash, stash->buffer_size);
			if (!line)
				return (NULL);
		}
		set_stash(stash, 0);
		read_bytes = read_file(fd, stash);
		if (read_bytes == -1 || (read_bytes == 0 && stash->buffer_size == 0))
		{
			free(line);
			return(NULL);
		}
		if (read_bytes < BUFFER_SIZE)
		{
			line = move_stash_to_line(line, stash, stash->buffer_size);
			set_stash(stash, 0);
			return (line);
		}
	}
}

char	*get_next_line(int fd)
{
	static struct	s_stash stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (stash.buffer_pos == NULL)
		stash.buffer_pos = stash.buffer;
	return(build_line(fd, &stash, line));
}

/*static int *p = NULL;
if (!p)
	p = (int *)malloc(sizeof(int));*/

/* #include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	int file;
	char *read_line;

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
					break;
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
}
 */