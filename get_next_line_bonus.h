/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 12:33:48 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/05/12 12:33:57 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_list
{
	int				l_fd;
	char			*l_tail;
	struct s_list	*l_next;
}					t_list;

int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *str, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(const char *s1);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
