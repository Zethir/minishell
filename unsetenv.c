/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 17:12:34 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 21:18:33 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_valid_arg(t_lst *node, char **arg)
{
	t_lst	*tmp;

	tmp = node;
	while (*arg)
	{
		while (node)
		{
			if (ft_strcmp(node->name, *arg) == 0)
				node->line = NULL;
			node = node->next;
		}
		node = tmp;
		arg++;
	}
}

int			do_unsetenv(t_lst *node, char *line)
{
	char	**arg;

	arg = ft_strsplit(line, ' ');
	arg++;
	if (!*arg)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
		check_valid_arg(node, arg);
	ft_strdel(arg);
	return (-1);
}
