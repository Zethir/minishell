/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:45:03 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/27 19:13:46 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**check_arg(t_lst *node, char *arg, char **save)
{
	t_lst	*tmp;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, arg) == 0)
		{
			*save = ft_strdup(node->line);
			node->line = NULL;
		}
		node = node->next;
	}
	node = tmp;
	return (save);
}

static int	check_u_opt(t_lst *node, char **arg, char **save)
{
	int i;

	i = 0;
	if (arg[i][0] == '-' && arg[i][1] == 'u' && !arg[i][2] && arg[i + 1])
	{
		i++;
		save = check_arg(node, arg[i], save);
		if (!save || !(*save))
			print_error_opt(arg[i]);
		else if (arg[i + 1])
			print_error_opt(arg[i + 1]);
		else
			print_env(node);
		return (0);
	}
	else
		return (1);
}

char		**deal_with_opt(t_lst *node, char *line)
{
	char	**arg;
	char	**save;
	int		i;

	i = 0;
	arg = ft_strsplit(&line[4], ' ');
	save = (char **)malloc(sizeof(char *) * 10);
	if (check_u_opt(node, arg, save) == 1)
	{
		if (!arg[i + 1] && arg[i][1] == 'u')
			print_error_arg();
		else
			print_main_error(&*arg[0]);
	}
	return (save);
}
