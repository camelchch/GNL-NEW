/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 12:46:20 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	int		i;
	int		j;
	static	int		line_ct;
	char	*buff;
	int		end_file;
	static	char stock[BUFF_SIZE];
	char	*temp;
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	end_file = 0;
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
	{
		if (!(*line = (char *)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		return (1);
	}
	line_ct = i;
	/*
	if (!line_ct)
	{
		if (!(temp = (char *)malloc(line_ct)))
			return (-1);
		temp = ft_strncpy(temp, (const char *)stock, i);
	}
	*/
	while (!end_file)
	{
		j = 0;
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		i = read(fd, buff, BUFF_SIZE);
		if ( i == -1)
			return (-1);
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		if (buff[j] != '\n' && i == BUFF_SIZE)
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			if (!add[0])
			add = ft_strcpy (add, stock);
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			free(buff);
		}
		else
		{
			if (!(*line = (char *)malloc(line_ct + j + 1)))
				return (-1);
			*line = ft_memmove (*line, stock, BUFF_SIZE);
			*line = ft_strncat(*line, (const char *)buff, j);
			ft_bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 1), BUFF_SIZE - j - 1);
			if (i < BUFF_SIZE)
			{
				end_file = 1;
				return (0);
			}
			return (1);
		}
	}
	return (0);
}

#include <fcntl.h>

int main(int ac, char **av)
{
	char *line;
	int		fd;
	(void) ac++;

	//line = 0;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd,&line))
	{
	ft_putendl(line);
	}
	return (0);
}
