/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 18:16:41 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

void	next_n(int	fd, int size, get_next *f)
{
	char	buff[BUFF_SIZE];

	f->k = 1;
	while (!(f->end_file) && !(f->end_line))
	{
	i = read(fd, buff, size);
	while (f->y < size && buff[f->y] && buff[f->y] != '\n')
		(f->y)++;
		f->add = (char *)malloc(size * f->k);
		if (f->k == 1)
			f->add = ft_strcpy(f->add, buff);
		else
		f->temp = f->add;
		f->add = ft_strncat(f->add, (const char *)buff, BUFF_SIZE);
		if (buff[f->y] == '\n')
			f->end_line = 1;
		if(f->j < size)
			f->end_file = 1;
		(f->k)++;
		free(f->temp);
		free(buff);
	}
}


int		get_next_line(const int fd, char **line)
{
	get_next	*f;

	f = (get_next *)malloc(sizeof(get_next));
	f->i = 0;
	f->j = 0;
	f->line_ct = 0;
	f->end_file = 0;
	f->end_line = 0;
	while (f->i < BUFF_SIZE && (f->stock)[f->i] && (f->stock)[f->i] != '\n')
		(f->i)++;
	if ((f->stock)[f->i] == '\n')
	{
		if (!(*line = (char *)malloc(f->i + 1)))
			return (-1);
		*line = ft_strncpy(*line, f->stock, f->i);
		while (f->i + 1 < BUFF_SIZE)
			(f->stock)[(f->j)++] = (f->stock)[(f->i)++ + 1];
		return (1);
	}
	f->line_ct = f->i;
	next_n(fd, BUFF_SIZE, f);
	*line = (char *)malloc(f->i + (f->x - 1) * BUFF_SIZE + f->y + 1);
	if((f->stock)[0])
	*line = ft_strncpy(*line, f->stock, f->i);
	*line = ft_strncat(*line, f->add, (f->x - 1) * BUFF_SIZE + f->j);
	f->t = (f->x - 1) * BUFF_SIZE + f->y + 1;
	f->i = 0;
	while ( f->t < BUFF_SIZE)
		(f->stock)[(f->i)++] = (f->add)[(f->t)++];
	return (1);
}







/*
	while (!end_file && !end_line)
	{
		j = 0;
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		i = read(fd, buff, BUFF_SIZE);
		ft_putendl("here check buff55555555555");
		ft_putendl(buff);
		if ( i == -1)
			return (-1);
		if (i < BUFF_SIZE)
			end_file = 1;
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		ft_putstr("here check j 88888888888");
		ft_putnbr(j);
		ft_putendl("");
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			if (!add[0])
				add = ft_strcpy (add, stock);
			temp = add;
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			ft_putstr("add is now=");
			ft_putendl(add);
			free(temp);
			free(buff);
		}
		else
			end_line = 1;
	}
	ft_putendl("heyhey 77777777777777777");
	ft_putnbr(j);
	ft_putnbr(line_ct);
	if (!(*line = (char *)malloc(line_ct + j + 1)))
		return (-1);
	*line = ft_memmove (*line, stock, BUFF_SIZE);
	ft_putendl(add);
	*line = ft_strncpy (*line, add, line_ct);
	ft_putendl("test line here 00000");
	ft_putendl(*line);
	*line = ft_strncat(*line, (const char *)buff, j);
	ft_putendl("test line here 1111");
	ft_putendl(buff);
	ft_putendl(*line);
	ft_bzero(stock, BUFF_SIZE);
	t = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 1), BUFF_SIZE - j - 1);
	if (i < BUFF_SIZE)
	{
		end_file = 1;
		return (0);
	}
	return (1);
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
*/
