/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdchane <mdchane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:32:40 by mdchane           #+#    #+#             */
/*   Updated: 2018/11/20 09:47:17 by mdchane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int     index_end_line(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

char    *ft_read_it(char *str, int fd)
{
    int     nbread;
    char    buff[BUFF_SIZE + 1];

    while ((nbread = read(fd, (void *)buff, BUFF_SIZE)) > 0)
    {
        buff[nbread] = '\0';
        str = ft_strjoin(str, buff);
    }
    return (str);
}

int    get_next_line(const int fd, char **line)
{
    
    static char *str;
    int         i;

    /*if (fd < 0 || line == NULL || fd < 10240)
        return (-1);*/
    str = ft_strnew(BUFF_SIZE + 1);
    *line = ft_strnew(BUFF_SIZE + 1);
    str = ft_read_it(str, fd);
    i = 0;
    if (str[i])
    {
        i = index_end_line(str);
        if (i == 0)
            *line = ft_strdup("");
        else if (i > 0)
        {
            *line = ft_strsub(str, 0, i + 1);
            str = str + i + 1;
        }
        return (1);
    }
    return (0);
}

/*int        get_next_line(const int fd, char **line)
{
}
*/

int     main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     ret;

    if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
    while (get_next_line(fd, &line) == 1)
	{
		ft_putstr(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
    return (0);
}
