/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 16:28:16 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 19:30:25 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_path(t_lst *node)
{
	t_lst			*tmp;
	char			**path;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "PATH") == 0)
		{
			if (node->line)
				path = ft_strsplit(&node->line[5], ':');
			else
				return (NULL);
		}
		node = node->next;
	}
	node = tmp;
	return (path);
}

static char	*check_path(char **path, char *arg)
{
	DIR				*dir;
	struct dirent	*ret;

	while (*path)
	{
		if ((dir = opendir(*path)))
		{
			while ((ret = readdir(dir)))
			{
				if (ft_strcmp(ret->d_name, arg) == 0)
				{
					closedir(dir);
					return (*path);
				}
			}
			closedir(dir);
		}
		path++;
	}
	return (NULL);
}

void		check_command(t_lst *node, char **arg, char *right_path, char **env)
{
	pid_t			pid;
	char			*str;

	if (access(ft_strjoin(right_path, *arg), X_OK) != -1)
	{
		pid = fork();
		if (pid > 0)
			wait(0);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			str = ft_strjoin(right_path, *arg);
			if (execve(str, arg, env) == -1)
				no_command_error(*arg);
			exit(0);
		}
	}
	else
		print_right_error(node, *arg);
}

static char	**get_env(t_lst *node)
{
	t_lst	*tmp;
	char	**env;
	int		i;

	tmp = node;
	i = get_index(node);
	env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (node)
	{
		if (node->line)
		{
			env[i] = ft_strdup(node->line);
			i++;
			node = node->next;
		}
		else
			node = node->next;
	}
	env[i] = NULL;
	node = tmp;
	return (env);
}

int			deal_with_command(t_lst *node, char **arg)
{
	char			**path;
	char			*right_path;
	char			**env;

	path = split_path(node);
	env = get_env(node);
	if (path && *arg && env)
	{
		right_path = check_path(path, *arg);
		if (right_path)
		{
			right_path = ft_strjoin(right_path, "/");
			check_command(node, arg, right_path, env);
			return (-1);
		}
	}
	if (*arg && *env)
	{
		right_path = "";
		check_command(node, arg, right_path, env);
	}
	return (-1);
}
