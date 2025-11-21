/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/21 14:29:43 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		stash[2048];
	char			*buffer;
	char			*newline;
	static ssize_t	count;
	// below are needed AFTER the while loop
	char            *line;
	ssize_t			read_bytes;
	ssize_t			line_bytes;
	ssize_t			stash_bytes;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	newline = NULL;
	if (count > 0)
	{
		newline = ft_memchr(stash, '\n', count);
		if (newline)
		{
			line_bytes = (newline - stash) + 1;
			line = ft_calloc((line_bytes + 1), sizeof(char));
			ft_memcpy(line, stash, line_bytes);
			stash_bytes = count - line_bytes;
			ft_memcpy(stash, stash + line_bytes, stash_bytes);
			count = stash_bytes;
			return (line);
		}
	}
	while (!newline)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break;
		newline = ft_memchr(buffer, '\n', read_bytes);
		if (!newline)
		{
			ft_memcpy(stash + count, buffer, read_bytes);
			count += read_bytes;
		}
	}
	// NEW FUNCTION STARTING HERE?
	if (read_bytes >= 0 && count > 0)
	{
		line_bytes = 0;
		if (newline)
			line_bytes = (newline - buffer) + 1;
		line = ft_calloc((count + line_bytes + 1), sizeof(char));
		if (count > 0)
			ft_memcpy(line, stash, count);
		stash_bytes = 0;
		if (read_bytes > 0)
		{
			ft_memcpy(line + count, buffer, line_bytes);
			stash_bytes = read_bytes - line_bytes;
			ft_memcpy(stash + count, buffer + line_bytes, stash_bytes);
		}
		else
			ft_memset(stash, 0, count);
		count = stash_bytes;
		free(buffer);
		return (line);
	}
	free(buffer);
   	return (NULL);
}
/* USE THIS MAIN AND READ FILE FOR TESTING GET NEXT LINE
int	read_file(int file)
{
	char		buf[8192];
	ssize_t		len;

	while (1)
	{
		len = read(file, &buf, 8192);
		write(STDOUT_FILENO, &buf, len);
		if (len <= 0)
			break ;
	}
	return (len);
}

int	main(int ac, char **av)
{
	int	file;
	int	read_status;

	if (ac == 2)
	{
		file = open(av[1], O_RDONLY);
		if (file == -1)
			write(STDERR_FILENO, "Cannot read file.\n", 18);
		else
		{
			read_status = read_file(file);
			close(file);
			if (read_status == 0)
				return (0);
			else
				write(STDERR_FILENO, "Cannot read file.\n", 18);
		}
	}
	else if (ac < 2)
		write(STDERR_FILENO, "File name missing.\n", 19);
	else
		write(STDERR_FILENO, "Too many arguments.\n", 20);
	return (1);
} */


	// ================== NOTES ======================================
	// IS THIS A RECURSIVE FUNCTION???
	// THIS ACTUALLY NEEDS TO BE A LOOP THAT CALLS ITSELF UNTIL NEWLINE
    // OR EOF OR BYTES_READ < BUFFER_SIZE

	// DO WE NEED AN EDGE a case if (bytes_read < BUFFER_SIZE)
	//  END OF FILE
	//  concat BUFFER to LINE
	//  clean STASH
	//  return LINE
	
	// - STATIC VARIABLE  will be needed to store position in file
	// 	  so that every time I call the function it reads the *next* line
	// - read() - returns a size_t
	//    - parameters: int fd, void *buf, size_t nbyte);
	// 	  - works with a cursor or POINTER that advances as bytes are read
	//		this pointer starts at 0 the first time
	//	  - if asked to read 5 nbyes, it advances 5 and stocks them in the *buf
	// 	  - it returns the number of bytes actually read
	//    - eof returns 0, error returns -1
	//    - gnl will need to stash the contents of the read() buffer somewhere!
	//      ideally a string or a linked list (the latter is quicker)
	//    	- stash needs to be read to identify if there is a \n in read buf
	//      - stash needs to keep concatenating or linking buf reads into stash
	//        until an \n is found.
	//        - when found, the line up to \n will need to be stored separately
	//          and returned (up to and including the \n)
	//      - stash then needs to be cleaned of all characters returned by GNL.
	//		- if STASH is static, then whatever is left after cleanup will 
	//        survive for the next GNL call.
	// - open() - accessing a file in c (but used by the MAIN function, not gnl
	// - RETURN read line
	// 	  otherwise return NULL (end of file or error)
	// - Compilation with -D BUFFER_SIZE=n (but function should handle a default
	//    value ... so if(!BUFFER_SIZE) buf = my_default_value


