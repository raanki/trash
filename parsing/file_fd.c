/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:58:54 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:47:55 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"


int    create_file(char *name)
{
    int fd;

    fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);

    /*if (fd == -1) {
        printf("erreur\n");
        perror("open");
        exit(EXIT_FAILURE);
    }*/
    close(fd);
    return (fd);
}

int     list_to_file(t_bracket *list)
{
    int fd;

    while(list)
    {
        fd = create_file(list->s);
        list = list->next;
    }
    return (fd);
}