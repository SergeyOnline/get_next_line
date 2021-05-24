/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:06:25 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/05/14 14:06:28 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int			ft_check_tail(char **line, char **tail)
{
	char *new_line;
	char *ptr;

	if (*tail)
		if ((new_line = ft_strchr(*tail, '\n')))
		{
			*new_line = '\0';
			if (!(*line = ft_strdup(*tail)))
				return (1);
			ptr = *tail;
			if (!(*tail = ft_strdup(new_line + 1)))
				return (1);
			free(ptr);
		}
		else
		{
			if (!(*line = ft_strdup(*tail)))
				return (1);
			free(*tail);
			*tail = NULL;
		}
	else if (!(*line = ft_strdup("\0")))
		return (1);
	return (0);
}

static int			ft_handle_gnl(int fd, char **line, char **tail)
{
	char		*new_line;
	char		buf[BUFFER_SIZE + 1];
	long		read_bytes;
	char		*ptr;

	read_bytes = 0;
	if (fd == -1 || (ft_check_tail(line, tail)) == 1)
		return (-1);
	while (!(*tail) && (read_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_bytes == -1)
			return (-1);
		buf[read_bytes] = '\0';
		if ((new_line = ft_strchr(buf, '\n')))
		{
			*new_line = '\0';
			if (!(*tail = ft_strdup(new_line + 1)))
				return (-1);
		}
		ptr = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		free(ptr);
	}
	return ((read_bytes || *tail) ? 1 : 0);
}

static t_list		*ft_lstnew(int fd)
{
	t_list *list;

	if ((list = (t_list *)malloc(sizeof(*list))))
	{
		list->l_fd = fd;
		list->l_tail = NULL;
		list->l_next = NULL;
	}
	else
		return (NULL);
	return (list);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_list			*ptr;

	if (!lst)
	{
		if (!(lst = ft_lstnew(fd)))
			return (-1);
		return (ft_handle_gnl(lst->l_fd, line, &(lst->l_tail)));
	}
	ptr = lst;
	while (ptr->l_fd != fd)
	{
		if (ptr->l_next == NULL)
		{
			ptr->l_next = ft_lstnew(fd);
			if (ptr->l_next == NULL)
				return (-1);
		}
		ptr = ptr->l_next;
	}
	return (ft_handle_gnl(ptr->l_fd, line, &(ptr->l_tail)));
}
