/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:41:43 by cboussau          #+#    #+#             */
/*   Updated: 2016/04/01 19:42:59 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>

# define RED "[31m"
# define PURPLE "[1;35m"
# define GREEN "[32m"
# define CYAN "[0;36m"
# define BLUE "[1;34m"
# define RESET "[39m"

typedef struct		s_lst
{
	char			*line;
	char			*name;
	char			*user;
	char			*home;
	struct s_lst	*next;
}					t_lst;

t_lst				*init_lst(char **env);
t_lst				*delete_elem(t_lst *node);
char				**deal_with_opt(t_lst *node, char **arg);
char				**malloc_tab(int i);
int					deal_with_env(t_lst *node, char *line);
int					ft_strccmp(const char *s1, const char *s2, char c);
int					do_setenv(t_lst *node, char *line);
int					do_unsetenv(t_lst *node, char *line);
int					print_alpha_error(char **arg);
int					do_exit(char *line);
int					do_cd(t_lst *node, char *line);
int					ft_strlen_char(char *str, char c);
int					deal_with_command(t_lst *node, char **arg);
int					get_index(t_lst *node);
int					check_lst(t_lst *node);
int					check_caract(char *str, char c);
void				push_node(t_lst *node, t_lst **head);
void				get_prompt(t_lst *node);
void				print_env(t_lst *node);
void				print_error_opt(char *arg);
void				print_main_error(char *arg);
void				print_error_arg(void);
void				print_env_error(char *arg);
void				no_command_error(char *arg);
void				deal_with_prompt_path(int i, char *buff);
void				color(char *color, char *str);
void				print_right_error(t_lst *node, char *arg);
void				free_list(t_lst *node);
void				add_elem(t_lst *node, char *arg);
void				check_command(t_lst *node, char **arg,
									char *right_path, char **env);
void				exec_right_path(t_lst *node, char **arg,
									char **env, char *right_path);

#endif
