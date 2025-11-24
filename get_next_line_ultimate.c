/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ultimate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedraza <mpedraza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:32 by mpedraza          #+#    #+#             */
/*   Updated: 2025/11/22 14:04:31 by mpedraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line_ultimate.h"

void	init_stash_state(struct s_stash_state *state)
{
	state->current_position = state->stash;
	// since it's static, is state->stash_len set to 0 automagically?
}

char	*get_next_line(int fd)
{
	static struct	s_stash_state state;
	char			*line;
	int				*read_bytes;

	init_stash_state(&state);


	if (line)
		return (line);
	return (NULL);
}

/*static int *p = NULL;
if (!p)
	p = (int *)malloc(sizeof(int));*/