/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 20:04:51 by saxiao           ###   ########.fr       */
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
	int		line_ct;
	int		end_file;
	char	buff[BUFF_SIZE];
	static	char stock[BUFF_SIZE];
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	end_file = 0;
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
	{
		*line = ft_strnew(i + 1);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		return (1);
	}
	line_ct = i;
	while (!end_file)
	{
		j = 0;
		i = read(fd, buff, BUFF_SIZE);
		ft_putstr("buff =");
		ft_putendl(buff);
		if ( i == -1)
			return (-1);
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		if (buff[j] != '\n' && i == BUFF_SIZE)
		{
			add = ft_strjoin((const char *)add, (const char *)buff);
		ft_putendl(add);
		}
		else
		{
			*line = ft_strnew(line_ct + j + 1);
			*line =  ft_strncpy(*line, stock, BUFF_SIZE);
			*line = ft_strjoin(*line, add);
			*line = ft_strncat(*line, (const char *)buff, j);
			ft_putstr("*line here is =");
			ft_putendl(*line);
			ft_bzero(stock, BUFF_SIZE);
			i = 0;
		while (j + 1 < BUFF_SIZE)
			stock[i++] = buff[j++ + 1];
			if (i < BUFF_SIZE)
			{
				end_file = 1;
				return (0);
			}
			return (1);
		}
	}
	return (1);
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
	ft_putendl("main here for testing 0000000");
	ft_putendl(line);
	}
	return (0);
}
