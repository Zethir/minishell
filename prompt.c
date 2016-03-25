/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:48:35 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/24 19:19:25 by cboussau         ###   ########.fr       */
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
	else
		ft_putstr("no USER var ");
}

static void	prompt_path(t_lst *node)
{
	t_lst	*tmp;
	char	*path;

	tmp = node;
	while (node)
	{
		if (ft_strncmp(node->line, "PWD=", 4) == 0)
		{	
			node->line = ft_strrchr(node->line, '/');
			path = ft_strdup(node->line);
		}
		node = node->next;
	}
	node = tmp;
	if (path)
	{
		color(PURPLE, "");
		ft_putchar('~');
		ft_putstr(path);
		color(RESET, "");
	}
	else
		ft_putstr("no PATH var ");
	color (RED, " \n$> ");
	color (RESET, "");
}

void		get_prompt(t_lst *node)
{
	prompt_name(node);
	prompt_path(node);
}
