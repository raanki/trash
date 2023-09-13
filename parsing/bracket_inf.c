/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_inf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:46:45 by ranki             #+#    #+#             */
/*   Updated: 2023/09/13 12:00:38 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// construct the list for the cmd with full redi
t_bracket *cmd_full_redi(char *s)
{
    t_bracket *lst;
    t_bracket *save;
    int start;
    int end;
    
    start = 0;
    end = 0;
    
    //FIRST CMD
    while(s && s[end] == ' ')
        end++;
    start = end;
    while(s && s[end] && s[end] != ' ' && s[end] != '<')
        end++;
    lst = new_bracket_node(strdup_like(s, start ,end));
    save = lst;

    // TRY FIND ALL OPTION
    while(s && s[end])
    {
        while (s[end] && s[end] != '-')
            end++;
        if (s[end] == '-')
        {
            start = end;
            while(s && s[end] && s[end] != ' ' && s[end] != '<')
                end++;
            lst->next = new_bracket_node(strdup_like(s, start ,end));
            lst = lst->next;
            continue ;
        }
    }

    // FIND LAST FILE 
    lst->next = new_bracket_node(strdup(trim_spaces(find_last_file(s))));
    lst = save;
    return (save);
}

void extract_files(char *s, t_bracket **lst)
{
    int i;
    int flag_redi;
    int start;
    int end;
    t_bracket *temp_lst = *lst;

    end = 0;
    flag_redi = 0;
    while(s && s[end] == ' ')
        end++;
    start = end;
    while(s && s[end] && s[end] != ' ' && s[end] != '<')
        end++;
    while(s && s[end])
    {
        while(s && s[end] == ' ')
            end++;
        if (s[end] == '-')
        {
            while(s && s[end] && s[end] != ' ' && s[end] != '<')
                end++;
            continue ;
        }
        else if (s[end] != '<')
        {
            if (flag_redi == 0)
            {
                start = end;
                while(s && s[end] && s[end] != ' ' && s[end] != '<')
                    end++;
                //printf("Ficher arg : \"%s\"\n", strdup_like(s, start, end));
                temp_lst->next = new_bracket_node(trim_spaces(strdup_like(s, start ,end)));
                temp_lst = temp_lst->next;
                continue ;
            }
            else if (flag_redi == 1)
            {
                while(s && s[end] && s[end] != ' ' && s[end] != '<')
                    end++;
                flag_redi = 0;
            }
        }
        else if (s[end] == '<')
        {
            flag_redi = 1;
            end++;
        }
    }
    *lst = temp_lst; 
}


// Create a list for redi < with cmd, arg and option
t_bracket *cmd_nofull(char *s)
{
    t_bracket *lst;
    t_bracket *save;
    int start;
    int end;
    
    start = 0;
    end = 0;
    //FIRST CMD
    while(s && s[end] == ' ')
        end++;
    start = end;
    while(s && s[end] && s[end] != ' ' && s[end] != '<')
        end++;
    lst = new_bracket_node(trim_spaces(strdup_like(s, start ,end)));
    save = lst;

    // TRY FIND ALL OPTION
    while(s && s[end])
    {
        while (s[end] && s[end] != '-')
            end++;
        if (s[end] == '-')
        {
            start = end;
            while(s && s[end] && s[end] != ' ' && s[end] != '<')
                end++;
            lst->next = new_bracket_node(strdup_like(s, start ,end));
            lst = lst->next;
            continue ;
        }
    }
    // FIND ALL VALID FILES
    extract_files(s, &lst);
    return (save);
}

char **list_to_array(t_bracket *lst)
{
    int         size;
    t_bracket   *tmp;
    char        **array;
    int         i;

    size = 0;
    tmp = lst;
    i = 0;
    while(tmp)
    {
        tmp = tmp->next;
        size++;
    }
    tmp = lst;
    array = malloc(sizeof(char *) * size + 1);
    array[size] = NULL;
    while(tmp)
    {
        array[i] = tmp->s;
        tmp = tmp->next;
        i++;
    }
    return (array);
}

// Main fonction for manage < redi
void    manage_bracket_inf(t_groups *cmd)
{
    char **array;
    t_bracket *lst;

    if (check_all_inf(cmd->s) != NULL)
    {
        printf("bash: %s: No such file or directory\n", check_all_inf(cmd->s));
        return ;
    }
    if (file_is_enlace(cmd->s) == 1)
    {
        lst = cmd_full_redi(cmd->s);
    }
    else
    {
        lst = cmd_nofull(cmd->s);
    }
    array = list_to_array(lst);
    //print_2d_array(array);
    command_exists_and_execute(array);
}