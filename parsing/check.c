/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:40:46 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:48:01 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	check_alone_token(t_token *token)
{
	if (token != NULL && token->token != NULL
		&& !command_exists(token->token))
	{
		if ((token->token[0] == '|' || token->token[1] == '\0' &&  token->token[0] != '>'))
		{
			printf("%s: command not found\n", token->token);
			return (0);
		}
	}
	return (1);
}

void	check_all(t_groups **list)
{
	t_groups	*current;
	t_token		*tmp;

	current = *list;
	while (current != NULL)
	{
		check_alone_token(current->list_token);
		current = current->next;
	}
}
