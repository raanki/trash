/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_utils_inf2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:40:22 by ranki             #+#    #+#             */
/*   Updated: 2023/09/13 11:54:47 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// allow to check if they are a option in the commande
void    check_option_parsing(int *i, char *s)
{
    while(s[*i] == ' ')
            (*i)++;
    while (s[*i] == '-')
    {
        while(s[*i] && (s[*i] != ' ' && s[*i] != '<' ))
            (*i)++;
        while(s[*i] == ' ')
            (*i)++;
    }
    while(s[*i] == ' ')
            (*i)++;
}

// allow to look is the command is a simple redi
int     file_is_enlace(char *s)
{
    int i;
    int word; // 1 = word 0 = '<'
    int first;

    i = 0;
    word = 1;
    first = 1;
    while(s && s[i])
    {
        if (word == 1 && first != 1 && s[i])
            return (0);
        first = 0;
        check_option_parsing(&i, s);
        while(s[i] == '<')
        {
            i++;
            word = 1;
        }
        while(s[i] == ' ')
            i++;
        if (word == 0 && s[i])
            return (0);
        while(s[i] && (s[i] != ' ' && s[i] != '<' ))
        {
            word = 0;
            i++;
        }
    }
    return (1);
}

// create the 2d string array for cmd and arguments
char    **create_array(char *s)
{
    char    **array;
    int     i;
    int     i_save;
    int     i_array;
    
    i = 0;
    array = malloc(sizeof(char *) * size_arg(s) + 1);
    i_array = 1;
    array[size_arg(s) + 1] = NULL;
    while(s && s[i] && i < size_arg(s) + 1)
    {
        while(s[i] == ' ' || s[i] == '<')
            i++;
        i_save = i;
        while(s[i] && s[i] != '<' && s[i] != ' ')
            i++;
        array[i_array] = trim_spaces(strdup_like(s, i_save, i));
        printf("\n \"%s\"\n", array[i_array]);
        i_array++;
        i++;
    }
    array[i_array + 1] = NULL;
    return (array);
}

// say if all file after redi was created
char    *check_all_inf(char *s)
{
    int i;
    int i_save;
    char *tmp_s;

    i = 0;
    while(s && s[i] && s[i] != '<')
        i++;
    while(s && s[i])
    {
        while(s[i] == ' ' || s[i] == '<')
            i++;
        
        if (s[i] == '-')
        { 
            while(s[i] && s[i] != '<' && s[i] != ' ')
                i++;
            continue ;
        }
        
        i_save = i;
        while(s[i] && s[i] != '<' && s[i] != ' ')
            i++;
        if (i != i_save)
        {
            tmp_s = strdup_like(s, i_save, i);
            //printf("\ntmp = %s\n", tmp_s);
            if (check_file_created(tmp_s) == 0)
                return (tmp_s);
            free(tmp_s);
        }
    }
    return (NULL);
}

// construct a new node for t_bracket struct
t_bracket *new_bracket_node(char *s)
{
    t_bracket *new;
    new = malloc(sizeof(t_bracket));
    new->next = NULL;
    new->s = s;
    return (new);
}