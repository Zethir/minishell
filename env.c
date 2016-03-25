/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:55:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/25 19:04:24 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_env(t_lst *node)
{
	t_lst *tmp;

	tmp = node;
	while (node)
	{
		ft_putendl(node->line);
		node = node->next;
	}
	node = tmp;
}

static int	cmp_line(t_lst *node, char **arg, char **save)
{
	int		i;
	char	*str;

	i = 0;
	while (node)
	{
		if (ft_strccmp(node->line, *arg, '=') == 0)
		{
			save[i] = ft_strdup(node->line);
			node->line = ft_strdup(*arg);
			str = ft_strdup(node->line);
		}
		node = node->next;
	}
	if (!str)
		str = "!@#$é";
	if (ft_strcmp(str, *arg) != 0)
	{
		ft_putstr("env: ");
		ft_putstr(*arg);
		ft_putendl(": No such file or directory");
		return (1);
	}
	return (0);
}

static char	**deal_with_arg(t_lst *node, char *line)
{
	t_lst	*tmp;
	char	**arg;
	char	**save;
	int		i;

	tmp = node;
	arg = ft_strsplit(&line[4], ' ');
	save = (char **)malloc(sizeof(char *) * 10);
	i = 0;
	while (*arg)
	{
		if (cmp_line(node, arg, save) == 0)
		{
			node = tmp;
			i++;
			arg++;
		}
		else
			return (NULL);
	}
	i = 0;
	print_env(node);
	return (&save[i]);
}

void		restore_env(t_lst *node, char **save)
{
	while (*save)
	{
		while (node)
		{
			if (ft_strccmp(node->line, *save, '=') == 0)
				node->line = ft_strdup(*save);
			node = node->next;
		}
		save++;
	}
}

void		deal_with_env(t_lst *node, char *line)
{
	char **save;

	if (line[3] == ' ' && line[4])
	{
		if (line[4] == '-')
			save = deal_with_opt(node, line);
		else
		{	
			save = deal_with_arg(node, line);
			if (!save)
				return ;
		}
		restore_env(node, save);
		free(&save);
	}
	else
		print_env(node);
}
