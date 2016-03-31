/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 19:39:25 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 19:20:28 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_list_arg(t_lst *node, char **arg)
{
	t_lst	*tmp;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, *arg) == 0)
		{
			node->line = ft_strjoin(*arg, "=");
			if (arg[1])
				node->line = ft_strjoin(node->line, arg[1]);
			return (1);
		}
		node = node->next;
	}
	node = tmp;
	return (0);
}

static void	handle_arg_setenv(t_lst *node, char **arg)
{
	t_lst *new_elem;

	if ((arg[0][0] >= 'A' && arg[0][0] <= 'Z') ||
			(arg[0][0] >= 'a' && arg[0][0] <= 'z'))
	{
		if (cmp_list_arg(node, arg) == 0)
		{
			new_elem = (t_lst *)malloc(sizeof(t_lst));
			new_elem->next = NULL;
			new_elem->line = ft_strjoin(*arg, "=");
			new_elem->name = ft_strdup(*arg);
			if (arg[1])
				new_elem->line = ft_strjoin(new_elem->line, arg[1]);
			push_node(new_elem, &node);
		}
	}
	else
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
}

int			do_setenv(t_lst *node, char *line)
{
	char	**arg;
	int		i;

	arg = ft_strsplit(line, ' ');
	arg++;
	i = 1;
	while (arg[i])
		i++;
	if (i > 2)
		ft_putendl_fd("setenv: Too many arguments", 2);
	else if (!*arg)
		print_env(node);
	else if (print_alpha_error(arg) == 1)
		return (-1);
	else
		handle_arg_setenv(node, arg);
	return (-1);
}
