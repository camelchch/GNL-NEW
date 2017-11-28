/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 19:40:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 20:03:58 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <string.h>

char*ft_strjoinfree(char const *s1, char const *s2)
{
	char*add;

	if		 (s1 && s2)
	{
		if (!(add = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
			return (NULL);
		add = ft_strcpy(add, s1);
		add = ft_strcat(add, s2);
		free((void*)s1);
		return (add);
	}
	return (NULL);
}

char	*ft_strcdup(const char *s, char c)
{
	char*copy;
	int i;

	i = 0;
	if (!(copy = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*s && *s != c)
		copy[i++] = *s++;
	copy[i] = '\0';
	return (copy);
}

int		get_next_line(int fd, char **line)
{
	static char *list = NULL;
	char		buffer[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0))
		return (-1);
	list = !list ? ft_strdup("") : list;
	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = 0;
		list = ft_strjoin(list, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (!(*list))
		return (0);
	if (ft_strchr(list, '\n'))
	{
		*line = ft_strcdup(list, '\n');
		while (*list != '\n')
			list++;
		list++;
	}
	else
	{
		*line = ft_strdup(list);
		list = ft_strdup("");
	}
	return (1);
}
