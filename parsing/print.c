/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:47:31 by ranki             #+#    #+#             */
/*   Updated: 2023/09/09 13:47:32 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// print a token list with all information

void	print_token_list(t_token *head)
{
	t_token	*current;
	int		i;

	i = 1;
	current = head;
	printf("\n\033[31m*************************************************\n");
	printf("*******************PRINT TOKEN LIST**************");
	printf("\n*************************************************\033[0m\n\n");
	while (current != NULL)
	{
		printf("\n*******************TOKEN NODE %d*******************\n\n", i);
		printf("\033[36mToken: %s\033[0m\n", current->token);
		printf("\033[32mType: %s\033[0m\n", print_enum(current->type));
		printf("d_flag: %d\n", current->d_flag);
		printf("s_flag: %d\n", current->s_flag);
		printf("edir_in_flag: %d\n", current->edir_in_flag);
		printf("redir_out_flag: %d\n", current->redir_out_flag);
		printf("var_flag: %d\n", current->var_flag);
		i++;
		current = current->next;
	}
	printf("\n*******************END TOKEN LIST*****************\n\n");
}

// print first divsion by separator "|"

void	print_groups_list(t_groups *head)
{
	t_groups	*current;
	int			i;

	i = 1;
	current = head;
	printf("\n\033[31m*************************************************\n");
	printf("*******************PRINT GROUPS******************");
	printf("\n*************************************************\033[0m\n\n");
	while (current != NULL)
	{
		printf("\n*******************GROUPS NODE %d*******************\n\n", i);
		printf("\033[36mGroups : \"%s\"\033[0m\n", current->s);
		printf("fd_out : %d\n", current->fd_out);
		printf("bracket_inf : %d\n", current->bracket_inf);
		printf("bracket_sup : %d\n", current->bracket_sup);
		i++;
		current = current->next;
	}
	printf("\n*******************END GROUPS LIST*****************\n\n");
}

// print the name of enum and not the value
char	*print_enum(int value)
{
	if (value == 0)
		return ("CMD");
	else if (value == 1)
		return ("ARG");
	else if (value == 2)
		return ("OPTN");
	else if (value == 3)
		return ("SEPARTOR");
	else if (value == 4)
		return ("PIPE");
	else if (value == 5)
		return ("FD_IN");
	else if (value == 6)
		return ("FD_OUT");
	return ("DEFAULT");
}

void	print_all_tokenlist(t_groups *list)
{
	t_groups	*current;

	current = list;
	while (current != NULL && current->list_token != NULL)
	{
		print_token_list(current->list_token);
		current = current->next;
	}
}

void	print_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("\"%s\"\n", array[i]);
		i++;
	}
}

/*void	print_bracket_arraylist(t_bracket **bracket)
{
	printf("\n\n*** Affichage ***\n\n");
    printf("ligne CMD  = %s\n\n", bracket[0]->s);
    while(bracket[0])
    {
        printf("ligne ARG  = %s\n", tmp->s);
        tmp = tmp->next;
    }
    printf("\n");
    while(bracket [1])
    {
        printf("ligne FILE = %s\n", tmp2->s);
        tmp2 = tmp2->next;
    }
    printf("\nligne FDOUT  = %s\n\n", bracket[3]->s);
}*/
