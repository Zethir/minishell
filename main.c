/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:38:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 17:34:23 by cboussau         ###   ########.fr       */
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
		push_node(node, &head);
		env++;
	}
	return (head);
}

static int	do_arg(t_lst *node, char *line, char **arg)
{
	int i;

	i = 0;
	if (ft_strncmp(*arg, "exit", 4) == 0)
		i = do_exit(line);
	if (ft_strncmp(*arg, "env", 3) == 0)
		i = deal_with_env(node, line);
	if (ft_strncmp(*arg, "setenv", 6) == 0)
		i = do_setenv(node, line);
	//if (ft_strncmp(*arg, "unsetenv", 8) == 0)
	//	do_unsetenv(node, line);
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
		arg = ft_strsplit(line, ' ');
		if (do_arg(node, line, arg) >= 0)
			break;
	}
	printf("exit\n");
	return (i);
}

int			main(int ac, char **av, char **env)
{
	t_lst	*node;
	int		i;

	av = NULL;
	node = init_lst(env);
	if (ac == 1)
		i = main_minishell(node);
	else
		return (1);
	return (i);
}
