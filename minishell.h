/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:41:43 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 21:22:03 by cboussau         ###   ########.fr       */
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
	char			*path;
	struct s_lst	*next;
}					t_lst;

t_lst				*init_lst(char **env);
int					deal_with_env(t_lst *node, char *line);
int					ft_strccmp(const char *s1, const char *s2, char c);
int					do_setenv(t_lst *node, char *line);
int					do_unsetenv(t_lst *node, char *line);
int					print_alpha_error(char **arg);
int					do_exit(char *line);
int					ft_strlen_char(char *str, char c);
int					no_command_error(char *arg);
void				push_node(t_lst *node, t_lst **head);
void				get_prompt(t_lst *node);
void				print_env(t_lst *node);
void				print_error_opt(char *arg);
void				print_main_error(char *arg);
void				print_error_arg(void);
void				print_env_error(char *arg);
char				**deal_with_opt(t_lst *node, char **arg);

#endif
