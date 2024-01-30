/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsuka <kmatsuka@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:28:29 by kmatsuka          #+#    #+#             */
/*   Updated: 2023/10/17 16:24:51 by kmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	save = my_make_save(save, fd);
	if (!save || *save == '\0')
	{
		free(save);
		return (NULL);
	}
	my_split_save(&save, &line);
	if (!save)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
