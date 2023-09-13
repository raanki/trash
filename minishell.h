/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:09:06 by ranki             #+#    #+#             */
/*   Updated: 2023/09/12 18:07:21 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

/*********************************STRUCTURE*********************************/

enum	e_type_token {
	CMD,
	ARG,
	OPTN,
	SEPARATOR,
	PIPE,
	FD_IN,
	FD_OUT,
	DEFAULT,
};

typedef struct s_groups{
	char			*s;
	int				bracket_sup;
	int				bracket_inf;
	struct s_token	*list_token;
	struct s_groups	*prec;
	struct s_groups	*next;
	int				fd_out;
}t_groups;

typedef struct s_token
{
	char				*token;
	enum e_type_token	type;
	int					d_flag;
	int					s_flag;
	int					edir_in_flag;
	int					redir_out_flag;
	int					var_flag;
	struct s_token		*pre;
	struct s_token		*next;
}	t_token;


typedef struct s_bracket{
	char				*s;
	int				nb_bracket;
	struct s_bracket	*next;
} t_bracket;

/*********************************PARSING*********************************/

void		print_token_list(t_token *head);
int			find_size_pipe(char *s, int *i);
t_groups	*split_by_pipe(char *cmd);
char		*strdup_like(char *s, int start, int end);
char		*trim_spaces(char *s);
t_groups	*create_defaut_groups(char *str);
t_token		*create_defaut_token(char *s);
void		print_groups_list(t_groups *head);
void		tokenadd_back(t_token **lst, t_token *new);
t_token		*token_last(t_token *lst);
void		manage_tokenization(t_groups *groups);
void		first_step_tokenization(t_groups *groups);
char		*print_enum(int value);
void		print_all_tokenlist(t_groups *list);
int			command_exists(char *cmd);
int			type_token(t_groups **list);
int			check_alone_token(t_token *token);
void		check_all(t_groups **list);
int			command_exists_and_execute(char **cmd);
char		**create_table_arg(t_groups *list);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		print_2d_array(char **array);
void    	updates_quotes_var(t_token *token);
void    	updates_quotes_cmd(t_groups *groups);
void		print_bracket_arraylist(t_bracket **bracket);
t_bracket   **manage_bracket(t_groups *cmd);
char	 	**merge_bracket_lists(t_bracket *list1, t_bracket *list2);
int			create_file(char *name);
int   		create_file(char *name);
int			list_to_file(t_bracket *list);
t_bracket	*bracket_last(t_bracket *lst);
int			still_one_bracket(char *s);
char		**merge_bracket_lists_inf(t_bracket *list1, t_bracket *list2);
int			still_one_bracket_inf(char *s);
void    	manage_bracket_inf(t_groups *cmd);
t_bracket	**create_bracket_arraylist(t_groups *cmd);
int			check_file_created(char *s);
char		*grep_commande_ofredi(char *s);
int			still_one_bracket_inf(char *s);
int			size_arg(char *s);
void    	check_option_parsing(int *i, char *s);
int     	file_is_enlace(char *s);
char    	**create_array(char *s);
char    	*check_all_inf(char *s);
t_bracket	*new_bracket_node(char *s);
char		*find_last_file(char *command);
t_groups	*main_split(char *s);



#endif