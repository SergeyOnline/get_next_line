/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:06:25 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/05/14 14:06:28 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_check_tail(char **line, char **tail)
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

int			get_next_line(int fd, char **line)
{
	char		*new_line;
	char		buf[BUFFER_SIZE + 1];
	long		read_bytes;
	static char *tail;
	char		*ptr;

	if (fd == -1 || (ft_check_tail(line, &tail)) == 1)
		return (-1);
	while (!tail && (read_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		if (read_bytes == -1)
			return (-1);
		buf[read_bytes] = '\0';
		if ((new_line = ft_strchr(buf, '\n')))
		{
			*new_line = '\0';
			if (!(tail = ft_strdup(new_line + 1)))
				return (-1);
		}
		ptr = *line;
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
		free(ptr);
	}
	return ((read_bytes || tail) ? 1 : 0);
}
