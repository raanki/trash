/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:58:54 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:47:58 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_token	*create_defaut_token(char *s)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = s;
	node->type = DEFAULT;
	node->d_flag = 0;
	node->s_flag = 0;
	node->edir_in_flag = 0;
	node->redir_out_flag = 0;
	node->pre = NULL;
	node->next = NULL;
	node->var_flag = 0;
	return (node);
}

t_groups	*create_defaut_groups(char *str)
{
	t_groups	*groups;

	groups = malloc(sizeof(t_groups));
	if (groups == NULL)
		return (NULL);
	groups->s = str;
	groups->next = NULL;
	groups->list_token = NULL;
	groups->fd_out = 1;
	groups->bracket_sup = 0;
	groups->bracket_inf = 0;
	return (groups);
}
