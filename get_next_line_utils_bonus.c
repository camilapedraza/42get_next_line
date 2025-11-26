/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:30:19 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/26 16:22:07 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	dest = malloc((len1 + len2 + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len1)
		dest[i++] = *(s1++);
	i = 0;
	while (i < len2)
		dest[len1 + i++] = *(s2++);
	dest[len1 + len2] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	slen;
	int		i;

	slen = ft_strlen(s);
	dup = malloc(slen + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (*s)
		dup[i++] = *s++;
	dup[i] = '\0';
	return (dup);
}
