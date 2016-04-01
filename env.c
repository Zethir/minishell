/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:55:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/04/01 19:48:24 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_env(t_lst *node)
{
	t_lst *tmp;

	tmp = node;
	while (node)
	{
		if (!node->line)
			node = node->next;
		else
		{
			ft_putendl(node->line);
			node = node->next;
		}
	}
	node = tmp;
}

static char	*cmp_line(t_lst *node, char **arg, char *save)
{
	t_lst	*tmp;

	tmp = node;
	while (node)
	{
		if (ft_strccmp(node->line, *arg, '=') == 0)
		{
			save = ft_strdup(node->line);
			node->line = ft_strdup(*arg);
		}
		node = node->next;
	}
	node = tmp;
	if (!save)
	{
		if (check_caract(*arg, '=') == 1)
			add_elem(node, *arg);
		else
			print_error_opt(*arg);
	}
	return (save);
}

static char	**deal_with_arg(t_lst *node, char **arg)
{
	char	**save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i])
		i++;
	save = malloc_tab(i);
	i = 0;
	while (*arg)
	{
		save[i] = cmp_line(node, arg, save[i]);
		if (!save[i])
			j++;
		i++;
		arg++;
	}
	print_env(node);
	while (j > 0)
	{
		node = delete_elem(node);
		j--;
	}
	return (save);
}

void		restore_env(t_lst *node, char **save)
{
	t_lst	*tmp;

	tmp = node;
	while (*save)
	{
		while (node)
		{
			if (ft_strncmp(node->name, *save, ft_strlen(node->name)) == 0)
				node->line = ft_strdup(*save);
			node = node->next;
		}
		node = tmp;
		save++;
	}
}

int			deal_with_env(t_lst *node, char *line)
{
	char	**save;
	char	**arg;

	arg = ft_strsplit(line, ' ');
	arg++;
	if (*arg)
	{
		if (*arg[0] == '-')
			save = deal_with_opt(node, arg);
		else
			save = deal_with_arg(node, arg);
		if (!save || !*save)
			return (-1);
		restore_env(node, save);
		free(save);
	}
	else
		print_env(node);
	return (-1);
}
