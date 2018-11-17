/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdchane <mdchane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:32:40 by mdchane           #+#    #+#             */
/*   Updated: 2018/11/17 12:52:47 by mdchane          ###   ########.fr       */
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

int    get_next_line(const int fd, char **line)
{
    size_t      nbread;
    char        *buff;
    static char *str;
    int         i;

    if (fd < 0 || line == NULL || fd < 10240)
    buff = ft_strnew(BUFF_SIZE);
    str = ft_strnew(BUFF_SIZE);
    line = (char **)malloc(sizeof(char *));
    *line = ft_strnew(BUFF_SIZE);
    while ((nbread = read(fd, (void *)buff, BUFF_SIZE)) > 0)
    {
        buff[nbread] = '\0';
        str = ft_strjoin(str, buff);
        i = index_end_line(str);
        if (i > -1)
        {
            *line = ft_strsub(str, 0, i + 1);
            return (1);
        }
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
    char    **line;
    int     ret;

    (void)argc;
    fd = open(argv[1], O_RDONLY);
    while ((ret = get_next_line(fd, line)) > 0)
    {
        ft_putendl(*line);
        free(*line);
    }
    close(fd);
    return (0);
}
