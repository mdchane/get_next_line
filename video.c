/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdchane <mdchane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:55:12 by mdchane           #+#    #+#             */
/*   Updated: 2018/11/15 16:15:54 by mdchane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int     readlinewidth(int fd)
{
    char    buff[2];
    size_t  nbread;

    memset((void *)buff, 0, 2);
    nbread = read(fd, (void *)buff, 2);
    if (nbread == -1 || nbread == 0)
        return (-1);
    buff[1] = '\0';
    return (atoi(buff));
}

void    readandprintlines(int fd, size_t linewidth)
{
    char    *buff;
    size_t  nbread;

    buff = (char *)malloc(sizeof(buff) * (linewidth + 1));
    if (buff == NULL)
        return ;
    memset((void *)buff, 0, linewidth + 1);
    while ((nbread = read(fd, (void *)buff, linewidth)) != 0)
    {
        printf("%s", buff);
        memset((void *)buff, 0, linewidth);
    }
    free(buff);
    return ;
}
