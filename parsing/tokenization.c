/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:04:15 by ranki             #+#    #+#             */
/*   Updated: 2023/09/13 22:32:46 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

//start the tokenization for each node

void	manage_tokenization(t_groups *groups)
{
	t_groups	*current;

	current = groups;
	while (current != NULL)
	{
		first_step_tokenization(current);
		current = current->next;
	}
}
// divide the string word by word

void	first_step_tokenization(t_groups *groups)
{
	int	end;
	int	start;
	int	s_flag;
	int	d_flag;
	int	c_flag;

	s_flag = 0;
	d_flag = 0;
	c_flag = 0;
	start = 0;
	end = 0;
	while (groups->s && end < strlen(groups->s) && groups->s[end])
	{
		if ((end > 1 && groups->s[end - 1] == '\\' && groups->s[end] == '\"'))
		{
			end++;
		}
		if (s_flag == 0 && groups->s[end] == '\"')
		{
			d_flag = (d_flag + 1) % 2;
		}
		if (d_flag == 0 && groups->s[end] == '\'')
			s_flag = (s_flag + 1) % 2;
		
		// permet de faire les tokens des groupes en les séparants.
		if ((groups->s[end] == ' ' || groups->s[end] == '\0' || groups->s[end + 1] == '>'
			|| groups->s[end] == '>' || groups->s[end + 1] == '\0' || (end > 1 
			&& groups->s[end - 1] == '>') || groups->s[end] == '<') && (d_flag == 0)
			&& (s_flag == 0))
		{
			while(groups->s[end] == ' ' && groups->s[end + 1] == ' ')
				end++;
			if (groups->s[end] == '>')
			{
				end++;
				groups->bracket_sup = 1;
			}
			if (groups->s[end] == '<')
			{
				end++;
				groups->bracket_inf = 1;
			}
			if (groups->s[end + 1] == '\0')
				end++;
			while(groups->s[end] == ' ' && groups->s[end + 1] == ' ')
				end++;
			tokenadd_back(&(groups->list_token), create_defaut_token(trim_spaces
					(strdup_like(groups->s, start, end))));
			start = end;
		}
		end++;
	}
}


// give type to a token
int	type_token(t_groups **list)
{
	t_groups	*current;
	t_token		*tmp;

	current = *list;
	while (current != NULL)
	{
		tmp = current->list_token;
		while (tmp != NULL)
		{
			if (command_exists(tmp->token))
				tmp->type = 0;
			else if (tmp->token != NULL && tmp->token[0] == '|')
				tmp->type = 4;
			else if (tmp->token != NULL && tmp->token[0] == '-')
				tmp->type = 1;
			else if (tmp->token != NULL && tmp->token[0] == '>')
			{
				tmp->type = 5;
				if (tmp->token[1] == '>')
					tmp->edir_in_flag = 2;
				else
					tmp->edir_in_flag = 1;
			}
			else if (tmp->token != NULL && tmp->token[0] == '<')
			{
				tmp->type = 6;
				if (tmp->token[1] == '<')
					tmp->redir_out_flag = 2;
				else
					tmp->redir_out_flag = 1;
			}
			else if (tmp->token != NULL && tmp->token[0] == ';')
				return (0);
			else if (tmp->token != NULL && tmp->token[0] == '\\')
				return (0);
			else
				tmp->type = 1;
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (1);
}
