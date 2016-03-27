/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:41:43 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/27 20:45:35 by cboussau         ###   ########.fr       */
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
	struct s_lst	*next;
}					t_lst;

void				push_node(t_lst *node, t_lst **head);
t_lst				*init_lst(char **env);
void				get_prompt(t_lst *node);
void				deal_with_env(t_lst *node, char *line);
int					ft_strccmp(const char *s1, const char *s2, char c);
void				print_env(t_lst *node);
int					ft_strlen_char(char *str, char c);
char				**deal_with_opt(t_lst *node, char *line);
void				print_error_opt(char *arg);
void				print_main_error(char *arg);
void				print_error_arg(void);
void				do_setenv(t_lst *node, char *line);
int					print_alpha_error(char **arg);

#endif
