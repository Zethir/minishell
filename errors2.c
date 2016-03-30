/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:35:18 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/30 21:44:33 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_command_error(char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": Command not found.", 2);
}

int		arg_in_dir(t_lst *node, char *arg)
{
	t_lst			*tmp;
	struct dirent	*ret;
	DIR				*dir;
	char			*str;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "PWD") == 0)
		{
			if (node->line)
				str = ft_strchr(node->line, '/');
			else
				str = "./";
		}
		node = node->next;
	}
	node = tmp;
	if ((dir = opendir(str)))
		while ((ret = readdir(dir)))
			if (ft_strcmp(arg, ret->d_name) == 0)
				return (1);
	return (0);
}

void	print_right_error(t_lst *node, char *arg)
{
	if (access(arg, X_OK) == -1 && arg_in_dir(node, arg) == 0)
	{
		ft_putstr_fd("error: permission denied: ", 2);
		ft_putendl_fd(arg, 2);
	}
	else
		no_command_error(arg);
}
