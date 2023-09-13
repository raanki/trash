/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:48:41 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:48:45 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// updates var in token struct (important is supposed quotes closed)
void    updates_quotes_var(t_token *token)
{
    int i;
    
    i = 0;
    while(token && token->token && token->token[i])
    {
        if (token->token[i] == '\'')
        {
            token->s_flag = 1;
            break;
        }
        if (token->token[i] == '\"')
        {
            token->d_flag = 1;
            break;
        }
        i++;
    }
}

// updates for all token of each groups
void    updates_quotes_cmd(t_groups *groups)
{
    t_token *tmp;
    while(groups && groups->list_token)
    {
        tmp = groups->list_token;
        while(tmp)
        {
            updates_quotes_var(tmp);
            tmp = tmp->next;
        }
        groups = groups->next;
    }
}