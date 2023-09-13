/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   firstSplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:47:46 by ranki             #+#    #+#             */
/*   Updated: 2023/09/13 17:03:31 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//a function like strdup but it takes a start and end to copy

char	*strdup_like(char *s, int start, int end)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char) * (end - start + 1));
	if (!copy)
		return (NULL);
	while (s && s[start] && start < end)
	{
		copy[i] = s[start];
		i++;
		start++;
	}
	copy[i] = '\0';
	return (copy);
}

// allow you to trim spaces before and after the string and FREE the current
char	*trim_spaces(char *s)
{
	int		start;
	int		end;

	start = 0;
	end = strlen(s) + 1;
	while (s && s[start] == ' ')
		start++;
	while (s && (s[end] == ' ' || s[end] == '\0'))
		end--;
	return (strdup_like(s, start, end + 1));
}

// help to split the cmd
int	last_sup(char *s, int i)
{
	if (s && s[(i)] == '>')
		(i)++;
	while (s)
	{
		if (s[i] == '\0' || s[i] == '<' || s[i] == '|')
		{
			while (s[(i)] != '|' && s[i] != '\0' && s[i] != '<')
				(i)++;
			(i)--;
			return (1);
		}
		if (s[(i)] == '>')
			return (0);
		(i)++;
	}
	return (0);
}

int	last_inf(char *s, int i)
{
	if (s && s[(i)] == '<')
		(i)++;
	while (s)
	{
		if (s[i] == '\0' || s[i] == '>' || s[i] == '|')
		{
			while (s[(i)] != '|' && s[i] != '\0' && s[i] != '>')
					(i)++;
				(i)--;
			return (1);
		}
		if (s[i] == '<')
			return (0);
		(i)++;
	}
	return (0);
}



// il manque les "" et '' ATTENTION 
t_groups	*main_split(char *s)
{
	int			start;
	int			end;
	t_groups	*lst;
	t_groups	*save;

	lst = NULL;
	end = 0;
	start = 0;
	
	while (s[end] == ' ')
		end++;
	if (s[end] == '\0')
		return (NULL);
	
	while (s && s[end])
	{
		while (s[end] && s[end] != '>' && s[end] != '<' && s[end] != '|')
			end++;
		if (s[end] == '\0')
		{
			if (lst == NULL)
			{
				lst = create_defaut_groups(trim_spaces(strdup_like(s, start, end)));
				save = lst;
			}
			else
			{
				lst->next = create_defaut_groups(trim_spaces(strdup_like(s, start, end)));
				lst = lst->next;
			}
			return (save);
		}
		else if (s[end] == '>' && last_sup(s, end))
		{
			while (s[end] != '|' && s[end] != '\0' && s[end] != '<')
					end++;
				end--;
			if (lst == NULL)
			{
				lst = create_defaut_groups(trim_spaces(strdup_like(s, start, end + 1)));
				save = lst;
			}
			else
			{
				lst->next = create_defaut_groups(trim_spaces(strdup_like(s, start, end + 1)));
				lst = lst->next;
			}
			start = end;
		}
		else if (s[end] == '<' && last_inf(s, end))
		{
			while (s[end] != '|' && s[end] != '\0' && s[end] != '>')
					end++;
				end--;
			if (lst == NULL)
			{
				lst = create_defaut_groups(trim_spaces(strdup_like(s, start, end + 1)));
				save = lst;
			}
			else
			{
				lst->next = create_defaut_groups(trim_spaces(strdup_like(s, start, end + 1)));
				lst = lst->next;
			}
			start = end;
		}
		else if (s[end] == '|')
		{
			if (lst == NULL)
			{
				lst = create_defaut_groups(trim_spaces(strdup_like(s, start, end - 1)));
				save = lst;
				lst->next = create_defaut_groups(strdup("|"));
				lst = lst->next;
			}
			else
			{
				lst->next = create_defaut_groups(strdup("|"));
				lst = lst->next;
			}
			end++;
			start = end;
		}
			end++;
	}
	return (save);
}