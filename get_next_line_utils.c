/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsuka <kmatsuka@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:06:16 by kmatsuka          #+#    #+#             */
/*   Updated: 2023/10/17 16:25:44 by kmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_make_save(char *save, int fd)
{
	char	*buf;
	char	*tmp;
	ssize_t	len_read;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	len_read = 0;
	while (!len_read)
	{
		len_read = read(fd, buf, BUFFER_SIZE);
		if (len_read <= 0)
			break ;
		buf[len_read] = '\0';
		tmp = save;
		save = ft_strjoin(save, buf);
		free(tmp);
		while ((!save && len_read > -1)
			|| (len_read > 0 && buf[len_read - 1] != '\n'))
			len_read--;
	}
	free(buf);
	if (len_read == -1)
		return (NULL);
	return (save);
}

void	my_split_save(char **save, char **line)
{
	size_t	len_save;
	size_t	len_line;
	char	*tmp;

	len_save = 0;
	while (*save && (*save)[len_save])
		len_save++;
	len_line = 0;
	while (len_line < len_save)
	{
		if ((*save)[len_line++] == '\n')
			break ;
	}
	tmp = *save;
	*line = ft_substr(*save, 0, len_line);
	if (*line)
		*save = ft_substr(*save, len_line, len_save - len_line);
	free(tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = 0;
	while (s1 && s1[len_s1])
		len_s1++;
	len_s2 = 0;
	while (s2 && s2[len_s2])
		len_s2++;
	str = (char *)malloc(len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	tmp = str;
	while (len_s1--)
		*tmp++ = *s1++;
	while (len_s2--)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	char	*tmp;
	size_t	s_start;
	size_t	len_s;

	if (!s)
		return (NULL);
	s_start = (size_t)start;
	len_s = 0;
	while (s[len_s])
		len_s++;
	if (s_start >= len_s)
		len = 0;
	else if (len_s - s_start < len)
		len = len_s - s_start;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	tmp = substring;
	while (len--)
		*tmp++ = s[start++];
	*tmp = '\0';
	return (substring);
}
