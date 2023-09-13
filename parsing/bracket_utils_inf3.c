/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_utils_inf3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:43:09 by ranki             #+#    #+#             */
/*   Updated: 2023/09/12 14:44:25 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

// FIND LAST FILE OF COMMAND
char *find_last_file(char *command)
{
    char *last_file;
    char *token;

    last_file = NULL;
    token = strtok(command, "<");
    while (token != NULL)
    {
        token = strtok(NULL, " \t\n");
        if (token != NULL)
            last_file = token;
    }
    return last_file;
}