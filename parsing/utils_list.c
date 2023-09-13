/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:33:30 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:47:07 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//allow you to manage directly the last node of a token list

t_token	*token_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (token_last(lst->next));
}

// allow you tou add back a token to the list

void	tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = token_last(*lst);
		tmp->next = new;
	}
}

t_bracket	*bracket_last(t_bracket *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (bracket_last(lst->next));
}
