/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/20 16:21:09 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read, malloc, free

#include "get_next_line.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
		if (*(char *)(s++) == (char) c)
			return ((char *)--s);
	return (NULL);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char		*dup;
	long int	slen;

	slen = ft_strlen(s);
	dup = malloc(sizeof(char) * slen + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz > 0)
	{
		while (src[i] && size--)
			*dst++ = src[i++];
		*dst = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*src;
	char	*dest;
	size_t	slen;
	size_t	dsize;

	if (!s || len == 0)
		return (ft_calloc(1, 1));
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_calloc(1, 1));
	src = (char *)s + start;
	if ((start + len) < slen)
		dsize = len + 1;
	else
		dsize = ft_strlen(src) + 1;
	dest = ft_calloc(dsize, sizeof(char));
	if (!dest)
		return (NULL);
	src = (char *)s + start;
	ft_strlcpy(dest, src, dsize);
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
		while (n--)
			*((char *)(dest + n)) = *((char *)(src + n));
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	si;
	size_t	di;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	di = dlen;
	si = 0;
	if (siz == 0)
		return (slen);
	if (siz <= dlen)
		return (slen + siz);
	while (src[si] && si < (siz - dlen - 1))
		dst[di++] = src[si++];
	dst[di] = '\0';
	return (slen + dlen);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((char *)(s + i++)) = c;
	return (s);
}


char	*get_next_line(int fd)
{
	
	static char	stash[SSIZE_MAX];
	char		*line;
	char		*buffer;
	char		*newline;
	size_t		bytes_read;
	int			position =  0;

	//SSIZE_MAX 2147483647
	//	RW_MAX 2147479552
	// INITIALIZE THIS PROPERLY
	stash[0] = '\0';
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	// check for ERROR or END OF LINE
	if (bytes_read <= 0)
	{
		free(BUFFER);
		return (NULL);
	}
	// new function starting here =======
	else if (bytes_read < BUFFER_SIZE)
	// END OF FILE
	// concat BUFFER to LINE
	// clean STASH
	// return LINE
	else
	{
		// check buffer for newline
		newline = ft_memchr(buffer, '\n', bytes_read);
		// if newline exists, copy STASH to LINE
		if (newline)
			line = malloc(position + (newline - buffer);
			ft_memmove(stash + position, buffer, newline - buffer)
		// concatenate BUFFER up to newline to LINE
		// clean STASH
		// STASH remaining BUFFER after newline
		// return line
		if (newline)
		{
			 
			return (ft_substr(buffer, 0, (newline - buffer)));
		




		
	
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


}

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
}

