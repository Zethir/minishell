/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:48:35 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/27 21:37:34 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	color(char *color, char *str)
{
	ft_putchar_fd('\033', 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(str, 2);
}

static void	prompt_name(t_lst *node)
{
	t_lst	*tmp;
	char	*user;

	tmp = node;
	while (node)
	{
		if (ft_strncmp(node->line, "USER=", 5) == 0)
			user = ft_strsub(node->line, 5, ft_strlen(node->line) - 5);
		node = node->next;
	}
	node = tmp;
	if (user)
	{
		color(BLUE, "# ");
		color(RESET, "");
		color(CYAN, user);
		color(RESET, "");
		ft_putstr(" in ");
	}
}

static char	*get_pwd(t_lst *node)
{
	char	*old_line;
	char	*path;

	while (node)
	{
		if (ft_strncmp(node->line, "PWD=", 4) == 0)
		{
			old_line = ft_strdup(node->line);
			node->line = ft_strrchr(node->line, '/');
			if (node->line)
				path = ft_strdup(node->line);
			else
				path = "\0";
			node->line = ft_strdup(old_line);
		}
		node = node->next;
	}
	return (path);
}

static void	prompt_path(t_lst *node)
{
	t_lst	*tmp;
	char	*path;

	tmp = node;
	path = get_pwd(node);
	node = tmp;
	if (path)
	{
		color(PURPLE, "");
		ft_putchar('~');
		color(RESET, "");
		color(PURPLE, path);
		color(RESET, "");
	}
	color(RED, " \n$> ");
	color(RESET, "");
}

void		get_prompt(t_lst *node)
{
	prompt_name(node);
	prompt_path(node);
}
