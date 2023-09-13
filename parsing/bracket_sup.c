/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_sup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:40:46 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:50:46 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// beta version of this function because j'ai la flemme frere
t_bracket **create_bracket_arraylist(t_groups *cmd)
{
    t_bracket   **bracket;
    int         i;

    i = 0;
    bracket = malloc(sizeof(t_bracket *) * 4);
    while(i < 4)
    {
        bracket[i] = malloc(sizeof(t_bracket));
        bracket[i]->s = malloc(sizeof(char *) * 30);
        bracket[i]->s[0] = '\0';
        bracket[i]->next = NULL;
        i++;
    }
    return (bracket);
}

// supposed bracket and commands is corrects, this function does't check errors
// i know that the function is written any way.
//First  want to make sure that everything works and then i'll make it clean and standard. Sorry :)
// manage only > and >>


t_bracket   **manage_bracket(t_groups *cmd)
{
    t_bracket **bracket;
    t_bracket *tmp;
    t_bracket *tmp2;
    int     i_cmd;
    int     j;
    int     f;

    f = 0;
    i_cmd = 0;
    j = 0;
    bracket = create_bracket_arraylist(cmd);
    while(cmd && cmd->s && cmd->s[i_cmd])
    {
        if (cmd->s[i_cmd] == '>' || cmd->s[i_cmd] == ' ')
            break;
        bracket[0]->s[j] = cmd->s[i_cmd];
        i_cmd++;
        j++;
    }
    bracket[0]->s[j] = '\0';
    j = 0;
    tmp = bracket[1];
    tmp2 = bracket[2];

    while(cmd && cmd->s && cmd->s[i_cmd])
    {
        while(cmd && cmd->s && cmd->s[i_cmd] == ' ')
            i_cmd++;

        while(cmd->s[i_cmd] != '>' && cmd->s[i_cmd] != '\0' && 
                (i_cmd > 1 && cmd->s[i_cmd - 1] != '\0'))
        {
            //printf("on fais c = %c\n", cmd->s[i_cmd]);
            bracket[1]->s[j] = cmd->s[i_cmd];
            j++;
            bracket[1]->s[j]  = '\0';
            if (cmd->s[i_cmd] == ' ')
            {
                bracket[1]->next = malloc(sizeof(t_bracket));
                bracket[1]->next->s = malloc(sizeof(char *) * 30);
                bracket[1] = bracket[1]->next;
                bracket[1]->next = NULL;
                j = 0;
            }
            i_cmd++;
        }
        bracket[2]->nb_bracket = 0;
        // manage parsing > and >>
       while (cmd->s[i_cmd] && (cmd->s[i_cmd] == ' ' || cmd->s[i_cmd] == '>') && cmd->s[i_cmd])
       {
            if (cmd->s[i_cmd] == '>' && cmd->s[i_cmd + 1] == '>')
            {
                bracket[2]->nb_bracket = 2;
                i_cmd++;
            }
            else if (cmd->s[i_cmd] == '>' && cmd->s[i_cmd + 1] != '>')
                bracket[2]->nb_bracket = 1;
            i_cmd++;
       }
        //FILE
        while(cmd->s[i_cmd] != ' ' && cmd->s[i_cmd])
        {
            bracket[2]->s[f] = cmd->s[i_cmd];
            f++;
            bracket[2]->s[f] = '\0';
            if (cmd->s[i_cmd + 1] == ' ' && still_one_bracket(cmd->s + i_cmd))
            {
                bracket[2]->next = malloc(sizeof(t_bracket));
                bracket[2]->next->s = malloc(sizeof(char *) * 30);
                bracket[2] = bracket[2]->next;
                bracket[2]->next = NULL;
                f = 0;
            }
            i_cmd++;
        }
    }

    char    **result;
    int     fd;
    int     fd2;

    bracket[3] = bracket[2];
    result = merge_bracket_lists(bracket[0], tmp);
    list_to_file(tmp2);
    if (result && result[0] && result[0][0] != '\0')
    {
        while(tmp2)
        {
            //printf("Case = \"%s\"\n", tmp2->s);
            tmp2 = tmp2->next;
        }
        if (bracket[3]->nb_bracket == 2)
            fd = open(bracket[3]->s, O_RDWR | O_APPEND | O_CREAT, 0644);
        else
            fd = open(bracket[3]->s, O_RDWR | O_TRUNC | O_CREAT, 0644);
        fd2 = dup(1);
        dup2(fd, 1);
        command_exists_and_execute(result);
        dup2(fd2, 1);
        close(fd2);
        close(fd);
        return (bracket);
    }
}


char **merge_bracket_lists(t_bracket *list1, t_bracket *list2)
{
    int size1 = 1, size2 = 0;
    t_bracket *temp1 = list1;
    t_bracket *temp2 = list2;

    // premiere liste egale toujours 1:

    // Calculer la taille de la deuxième liste
    while (temp2 != NULL)
    {
        size2++;
        temp2 = temp2->next;
    }

    // Allouer de la mémoire pour le tableau 2D résultant
   char **result = malloc(sizeof(char *) * (size1 + size2 + 1));

    // Copier la première liste dans le tableau résultant
    temp1 = list1;
    for (int i = 0; i < size1; i++)
    {
        if (temp1->s == NULL || temp1->s[0] == '\0')
        {
            result[i] = strdup("");
            result[i + 1] = NULL;
            temp1 = temp1->next;
        }
        else
        {
            result[i] = strdup(temp1->s);
            result[i + 1] = NULL;
            temp1 = temp1->next;
        }
    }
    temp2 = list2;
    for (int i = size1; i < size1 + size2; i++)
    {
        result[i] = strdup(temp2->s);
        result[i + 1] = NULL;
        temp2 = temp2->next;
    }
    result[size1 + size2] = NULL;
    int i = 0;
    while(i < size1 + size2)
    {
        result[i] = trim_spaces(result[i]);
        i++;
    }
    //print_2d_array(result);
    return result;
}


int still_one_bracket(char *s)
{
    int i;

    i = 0;
    while(s && s[i])
    {
        if (s[i] == '>')
            return (1);
        i++;
    }
    return (0);
}