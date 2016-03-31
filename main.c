/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:38:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 19:21:47 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		push_node(t_lst *node, t_lst **head)
{
	t_lst	*tmp;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	else
		tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_lst		*init_lst(char **env)
{
	t_lst	*node;
	t_lst	*head;

	head = NULL;
	while (*env)
	{
		node = (t_lst *)malloc(sizeof(t_lst));
		if (!node)
			return (NULL);
		node->next = NULL;
		node->line = ft_strdup(*env);
		node->name = ft_strsub(*env, 0, ft_strlen_char(*env, '='));
		if (ft_strccmp(*env, "USER=", '=') == 0)
			node->user = ft_strsub(*env, 5, ft_strlen(*env) - 5);
		if (ft_strncmp(*env, "HOME=", 5) == 0)
			node->home = ft_strchr(*env, '/');
		push_node(node, &head);
		env++;
	}
	return (head);
}

static int	do_arg(t_lst *node, char *arg)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_strsplit(arg, ' ');
	if (ft_strncmp(*cmd, "exit", 4) == 0)
		i = do_exit(arg);
	else if (ft_strncmp(*cmd, "env", 3) == 0)
		i = deal_with_env(node, arg);
	else if (ft_strncmp(*cmd, "setenv", 6) == 0)
		i = do_setenv(node, arg);
	else if (ft_strncmp(*cmd, "unsetenv", 8) == 0)
		i = do_unsetenv(node, arg);
	else if (ft_strncmp(*cmd, "cd", 2) == 0)
		i = do_cd(node, arg);
	else if (*cmd)
		i = deal_with_command(node, cmd);
	return (i);
}

static int	main_minishell(t_lst *node)
{
	char	*line;
	char	**arg;
	int		i;

	line = NULL;
	i = 0;
	while (1)
	{
		get_prompt(node);
		if (get_next_line(0, &line) != 1)
			break ;
		arg = ft_strsplit(line, ';');
		while (*arg)
		{
			if (do_arg(node, *arg) >= 0)
			{
				ft_putstr("exit\n");
				exit(0);
			}
			arg++;
		}
	}
	return (i);
}

int			main(int ac, char **av, char **env)
{
	t_lst	*node;
	int		i;

	av = NULL;
	node = init_lst(env);
	signal(SIGINT, SIG_IGN);
	i = 0;
	if (ac == 1)
		i = main_minishell(node);
	else
		return (1);
	return (i);
}
