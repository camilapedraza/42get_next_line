/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ultimate.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:58:51 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/22 14:04:32 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
#  endif

struct s_stash_state
{
	char	*stash;
	size_t	stash_len; // how much data has been read into buffer, max is BUFLEN
	char	*current_position;
};

char	*get_next_line(int fd);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

# endif
