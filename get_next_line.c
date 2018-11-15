/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdchane <mdchane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:32:40 by mdchane           #+#    #+#             */
/*   Updated: 2018/11/15 16:15:53 by mdchane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void    read_it(const int fd)
{
    size_t      nbread;
    char        *buff;
    char        *str;

    buff = (char *)malloc(sizeof(buff) * (BUFF_SIZE + 1));
    if (buff == NULL)
        return ;
    memset((void *)buff, 0, BUFF_SIZE + 1);
    while ((nbread = read(fd, (void *)buff, BUFF_SIZE)) > 0)
    {
        buff[nbread] = '\0';
        str = ft_strjoin(str, buff);
        printf("%s\n", str);
    }
    printf("%s\n", str);
}

/*int        get_next_line(const int fd, char **line)
{
}
*/

int     main(int argc, char **argv)
{
    int     fd;

    (void)argc;
    fd = open(argv[1], O_RDONLY);
    read_it(fd);
    close(fd);
    return (0);
}
