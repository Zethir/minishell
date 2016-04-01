/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:45:03 by cboussau          #+#    #+#             */
/*   Updated: 2016/04/01 17:40:33 by cboussau         ###   ########.fr       */
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

static void	delete_env(t_lst *node)
{
	t_lst *tmp;

	tmp = node;
	while (node)
	{
		if (node->line)
			ft_strdel(&node->line);
		node = node->next;
	}
	node = tmp;
}

static int	check_i_opt(t_lst *node, char **arg)
{
	int i;

	i = 0;
	if (arg[i][0] == '-' && arg[i][1] == 'i' && !arg[i][2] && arg[i + 1])
	{
		while (arg[i])
			i++;
		if (i > 3)
		{
			ft_putendl_fd("env: Too many arguments.", 2);
			return (0);
		}
		delete_env(node);
		arg++;
		deal_with_command(node, arg);
		return (0);
	}
	else
		return (1);
}

static int	check_u_opt(t_lst *node, char **arg, char **save)
{
	int i;

	i = 0;
	if (arg[i][0] == '-' && arg[i][1] == 'u' && !arg[i][2] && arg[i + 1])
	{
		while (arg[i])
			i++;
		if (i > 3)
		{
			ft_putendl_fd("env: Too many arguments.", 2);
			return (0);
		}
		arg++;
		save = check_arg(node, *arg, save);
		if (!save || !(*save))
			print_error_opt(*arg);
		arg++;
		if (*arg)
			deal_with_command(node, arg);
		else
			print_env(node);
		return (0);
	}
	else
		return (1);
}

char		**deal_with_opt(t_lst *node, char **arg)
{
	char	**save;

	save = (char **)malloc(sizeof(char *) * 1);
	if (!save)
		return (NULL);
	if (check_u_opt(node, arg, save) == 1)
	{
		if (check_i_opt(node, arg) == 1)
		{
			if (!arg[1] && !arg[0][2] && (arg[0][1] == 'u' || arg[0][1] == 'i'))
				print_error_arg();
			else
				print_main_error(&*arg[0]);
			return (NULL);
		}
		else
			return (NULL);
	}
	return (save);
}
