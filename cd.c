/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 13:41:53 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 19:14:13 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		go_to_root(t_lst *node)
{
	t_lst		*tmp;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "HOME") == 0)
		{
			node->home = ft_strchr(node->home, '/');
			chdir(node->home);
			return ;
		}
		node = node->next;
	}
	node = tmp;
}

static char		*deal_with_root(t_lst *node, char *arg)
{
	char		*tmp;

	if (!arg[1])
		go_to_root(node);
	else if (arg[1] == '/')
	{
		go_to_root(node);
		if (arg[2])
			tmp = ft_strsub(arg, 2, ft_strlen(arg));
		else
			tmp = ft_strsub(arg, 1, ft_strlen(arg));
		return (tmp);
	}
	else
	{
		ft_putstr_fd("Unknown user: ", 2);
		ft_putstr_fd(&arg[1], 2);
		ft_putendl_fd(".", 2);
	}
	return (NULL);
}

static void		deal_with_cd_arg(char *arg)
{
	DIR			*dir;
	struct stat	st;

	dir = opendir(arg);
	if (stat(arg, &st) == -1)
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory.", 2);
	}
	else if (!(S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else if (access(arg, X_OK) == -1)
	{
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Permission denied: ", 2);
	}
	else
		chdir(arg);
	if (dir)
		closedir(dir);
}

int				do_cd(t_lst *node, char *line)
{
	char		**arg;
	int			i;

	arg = ft_strsplit(line, ' ');
	arg++;
	i = 0;
	while (arg[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("cd: Too many arguments.", 2);
		return (-1);
	}
	else if (!*arg)
		go_to_root(node);
	else if (*arg[0] == '~')
	{
		*arg = deal_with_root(node, *arg);
		if (!*arg)
			return (-1);
	}
	if (*arg)
		deal_with_cd_arg(*arg);
	return (-1);
}
