/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:55:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 18:43:36 by cboussau         ###   ########.fr       */
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
	int		i;
	char	*str;

	i = 0;
	while (node)
	{
		if (ft_strccmp(node->line, *arg, '=') == 0)
		{
			save = ft_strdup(node->line);
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
		return (NULL);
	}
	return (save);
}

static char	**deal_with_arg(t_lst *node, char **arg)
{
	t_lst	*tmp;
	char	**save;
	int		i;

	tmp = node;
	save = (char **)malloc(sizeof(char *) * 10);
	i = 0;
	if (!save)
		return (NULL);
	while (*arg)
	{
		save[i] = cmp_line(node, arg, save[i]);
		if (!save[i])
			return (NULL);
		node = tmp;
		i++;
		arg++;
	}
	print_env(node);
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
	char 	**save;
	char	**arg;

	arg = ft_strsplit(line, ' ');
	arg++;
	if (*arg)
	{
		if (*arg[0] == '-')
		{	
			save = deal_with_opt(node, arg);
			if (!save || !(*save))
				return (-1);
		}
		else
		{	
			save = deal_with_arg(node, arg);
			if (!save || !(*save))
				return (-1);
		}
		restore_env(node, save);
	}
	else
		print_env(node);
	return (-1);
}
