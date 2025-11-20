/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:48:35 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/20 12:24:32 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read, malloc, free

char *get_next_line(int fd)
{
	// - STATIC VARIABLE  will be needed to store position in file
	// 	  so that every time I call the function it reads the *next* line
	// - read() - returns a size_t
	//    - parameters: int fd, void *buf, size_t nbyte);
	// 	  - works with a cursor or POINTER that advances as bytes are read
	//		this pointer starts at 0 the first time
	//	  - if asked to read 5 nbyes, it advances 5 and stocks then in the *buf
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
	//    value
}
