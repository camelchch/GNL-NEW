/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 11:45:16 by saxiao           ###   ########.fr       */
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
	char	*buff;
	int		end_file;
	static	char stock[BUFF_SIZE];
	char	*temp;
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	end_file = 0;
	ft_putstr(stock);
	line = (char **)malloc(sizeof(char *));
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
	{
		i++;
		//printf("i here is %d \n", i);
	}
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
	ft_putnbr(i);
	ft_putendl("");
	if (!line_ct)
	{
		if (!(temp = (char *)malloc(line_ct)))
			return (-1);
		temp = ft_strncpy(temp, (const char *)stock, i);
	}
	i = 0;
	while (!end_file)
	{
		j = 0;
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		ft_putendl("test here 666666666666");
		i = read(fd, buff, BUFF_SIZE);
		ft_putendl(buff);
		if ( i == -1)
			return (-1);
		if (!i)
		{
			if (!line_ct)
			{
				*line = (char *)malloc(line_ct + 1);
				*line = ft_strcpy(*line, temp);
				end_file = 1;
			}
			return (0);
		}
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		ft_putnbr(j);
		//	printf("333333333 here  \n");
		//	printf("%s \n", buff);
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			if(temp)
			{
				add = ft_strcpy (add, temp);
			}
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			//free(temp);
			free(buff);
			temp = add;
			//printf("%s \n",temp);
		}
		else
		{
			//ft_putendl(buff);
			ft_putnbr(j);
			if (!(*line = (char *)malloc(line_ct + j + 1)))
				return (-1);
			//ft_putnbr(j);
			ft_putendl("right here 6666666666666666");
			temp = stock;
			*line = ft_memmove (*line, temp, j);
			ft_putendl("here 5555555555555555");
			ft_putnbr(j);
			ft_putendl("");
			*line = ft_strncat(*line, (const char *)buff, j);
			ft_putendl(*line);
			//free(temp);
			if (stock[0])
				ft_bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 1), BUFF_SIZE - j - 1);
			ft_putendl(stock);
			ft_putendl("");
		//	free (temp);
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
	int		t;

	//line = 0;
	fd = open(av[1], O_RDONLY);
	t = get_next_line(fd ,&line);
	ft_putendl("main 1111 here");
	ft_putendl("test main");
	ft_putendl(line);
	t = get_next_line(fd ,&line);
	//	ft_putendl("main 2222 here");
	//	ft_putendl(*line);
	return (0);
}
