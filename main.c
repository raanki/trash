/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:48:17 by ranki             #+#    #+#             */
/*   Updated: 2023/09/13 17:07:01 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_groups	*current_cmd;

	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		str = readline("?>");
		if (str == NULL)
			exit(0);
		if (str[0] != '\0')
		{
			add_history(str);
			current_cmd = main_split(str);
			if (current_cmd != NULL)
			{
				manage_tokenization(current_cmd);
				//print_groups_list(current_cmd);
				if(type_token(&current_cmd) == 0)
				{
					printf("';' and '/' aren't managed\n");
					continue ;
				}
				updates_quotes_cmd(current_cmd);
				//print_all_tokenlist(current_cmd);
				check_all(&current_cmd);
				if (current_cmd->bracket_sup == 0 && current_cmd->bracket_inf == 0)
					command_exists_and_execute(create_table_arg(current_cmd));
				else if (current_cmd->bracket_sup == 1)
				{
					//printf("J'analyse une redirection > superieur, je la traite :\n\n");
					manage_bracket(current_cmd);
				}
				else if (current_cmd->bracket_inf == 1)
				{
					//printf("J'analyse une redirection < inferieur, je la traite :\n\n");
					manage_bracket_inf(current_cmd);
				}
			}
		}
	}
}

// cat -e > test1 > test2 | grep ranki
//echo "ra|an" | grep a
// echo -n rayan | grep -v ra | grep salut
//echo rayan ; echo anki
// echo cat > fichier
//echo rayan > file2 anki > file3
// echo rayan > file | grep t
// echo rayan > file1 > file2 > file3
// echo 'Hello\"World'
// echo "Hello\'World"
// echo 'Hello\"World' | echo "Hello\'World"
// echo "Hello\"World"
// echo rayan > file1 anki myriam > file2 katia sami > file3
// > emptyfile
// echo -n rayan > file1 anki > file2
// echo -n rayan > file1 anki
// ls > file1 -l
// cat < test1 -n test2 < test3       => affiche test2 avec option -n
// cat file1 < file2 < file3
// cat < file2 < file3
//cat < file1
