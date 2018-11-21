/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdchane <mdchane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:32:40 by mdchane           #+#    #+#             */
/*   Updated: 2018/11/20 15:49:11 by mdchane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char    *ft_read_it(char **str, int fd)
{
    int     nbread;
    char    buff[BUFF_SIZE + 1];

    while ((nbread = read(fd, (void *)buff, BUFF_SIZE)) > 0)
    {
        buff[nbread] = '\0';
        *str = ft_strjoin(*str, buff);
        if (ft_strchr(*str, '\n'))
            return (*str);
    }
    return (*str);
}

int     ft_errors(char **str, int fd, char **line)
{
    if (fd < 0 || line == NULL || BUFF_SIZE < 0 || fd > OPEN_MAX)
        return (1);
    if (!(*str))
    {
        if (!(*str = ft_strnew(BUFF_SIZE)))
            return (1);
    }
    return (0);
}

int    get_next_line(const int fd, char **line)
{
    
    static char *str;
    int         i;

    if (ft_errors(&str, fd, line))
        return (-1);
    str = ft_read_it(&str, fd);
    i = 0;
    if (str[i])
    {
        while (str[i] && str[i] != '\n')
            i++;
        *line = ft_strsub(str, 0, i);
        str = &str[i + 1];
        return (1);
    }
    else
        *line = ft_strdup("");
    return (0);
}

int     main(int argc, char **argv)
{
    int     fd;
    char    *line;

    if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
    while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
	if (argc == 2)
		close(fd);
    return (0);
}
