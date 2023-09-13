/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:39:11 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:47:38 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	command_exists(char *cmd)
{
	char	*path;
	char	*p;
	char	cmd_path[1024];

	cmd[strlen(cmd)] = '\0';
	path = strdup(getenv("PATH"));
	p = strtok(path, ":");
	while (p != NULL)
	{
		strcpy(cmd_path, p);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (1);
		p = strtok(NULL, ":");
	}
	return (0);
}

int	command_exists_and_execute(char **cmd)
{
	char	*path;
	char	*p;
	char	cmd_path[1024];
	int		status;
	pid_t	pid;

	path = strdup(getenv("PATH"));
	p = strtok(path, ":");
	while (p != NULL)
	{
		strcpy(cmd_path, p);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(cmd_path, cmd, NULL);
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
				status = -1;
			else
				if (waitpid(pid, &status, 0) != pid)
					status = -1;
			return (status);
		}
		p = strtok(NULL, ":");
	}
	return (-1);
}

// transforms a list of token into an array

char	**create_table_arg(t_groups *list)
{
	t_groups	*current;
	t_token		*tmp;
	char		**array;
	int			i, j, k;

	array = malloc(sizeof(char *) * 10);
	current = list;
	i = 0;
	while (current != NULL)
	{
		tmp = current->list_token;
		while (tmp != NULL)
		{
			array[i] = malloc(sizeof(char) * (strlen(tmp->token) + 1));
			j = 0;
			k = 0;
			while (tmp->token[j] != '\0')
			{
				if (j == 0 && (tmp->token[j] == '\"' || tmp->token[j] == '\''))
					j++;
				if (tmp->token[j] && (tmp->token[j] == '\"' || tmp->token[j] == '\'')
						&& tmp->token[j + 1] == '\0')
					j++;
				if (tmp->d_flag == 1 && (tmp->token[j] == '\\' 
						&& (tmp->token[j + 1] == '\"' )))
					array[i][k++] = tmp->token[++j];
				else
					array[i][k++] = tmp->token[j];
				j++;
			}
			array[i][k] = '\0';
			tmp = tmp->next;
			i++;
		}
		array[i] = NULL;
		current = current->next;
	}
	return (array);
}

