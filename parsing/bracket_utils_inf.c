/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_utils_inf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:28:34 by ranki             #+#    #+#             */
/*   Updated: 2023/09/12 14:39:55 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// check if a file is created or not
int     check_file_created(char *s)
{
    int fd;

    fd = open(s, O_RDONLY);
    if (fd == -1)
        return (0);
    return (1);
}


// try to find the cmd of the input either return null
char *grep_commande_ofredi(char *s)
{
    int end;
    int start;

    end = 0;
    while(s && s[end] && s[end] == ' ')
        end++;
    start = end;
    while (s && s[end] && s[end] != '<' && s[end] != ' ')
        end++;
    if (end == 0)
        return (NULL);
    return (strdup_like(s, start, end));
}


// check if is still a bracket inf in the command
int still_one_bracket_inf(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if (s[i] == '<')
            return (1);
        i++;
    }
    return (0);
}

// give the number of arguments of commande
int size_arg(char *s)
{
    int nb;
    int i;

    i = 0;
    nb = 0;
    while(s && s[i])
    {
        while(s[i] == ' ' || s[i] == '<')
            i++;
        nb++;
        while(s[i] && s[i] != '<' && s[i] != ' ')
            i++;
    }
    return (nb);
}