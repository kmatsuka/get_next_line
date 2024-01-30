/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsuka <kmatsuka@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:28:40 by kmatsuka          #+#    #+#             */
/*   Updated: 2023/10/17 16:25:21 by kmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	my_lstset(t_list **lst, int fd)
{
	*lst = (t_list *)malloc(sizeof(t_list));
	if (!*lst)
		return (-1);
	(*lst)->fd = fd;
	(*lst)->str = NULL;
	(*lst)->next = NULL;
	return (0);
}

static void	my_free_lst(t_list **lst, t_list *now, int fd)
{
	t_list	*tmp;

	free(now->str);
	if ((*lst)->fd == fd)
		*lst = (*lst)->next;
	else
	{
		tmp = *lst;
		while (tmp->next != now)
			tmp = tmp->next;
		tmp->next = now->next;
	}
	free(now);
}

static t_list	*my_make_lst(t_list **lst, int fd)
{
	t_list	*head;
	t_list	*tmp;

	if (!*lst)
	{
		if (my_lstset(lst, fd))
			return (NULL);
		return (*lst);
	}
	head = *lst;
	while (*lst)
	{
		tmp = *lst;
		if ((*lst)->fd == fd)
			break ;
		if (!(*lst)->next)
		{
			if (my_lstset(&(*lst)->next, fd))
				return (NULL);
			tmp = (*lst)->next;
		}
		*lst = (*lst)->next;
	}
	*lst = head;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_list	*save;
	t_list			*now;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	now = my_make_lst(&save, fd);
	if (!now)
		return (NULL);
	now->str = my_make_save(now->str, now->fd);
	if (!now->str || *now->str == '\0')
	{
		my_free_lst(&save, now, fd);
		return (NULL);
	}
	my_split_save(&now->str, &line);
	if (!now->str || !line)
	{
		now->str = NULL;
		my_free_lst(&save, now, fd);
		free(line);
		return (NULL);
	}
	return (line);
}
