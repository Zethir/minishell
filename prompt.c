/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:48:35 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/29 15:45:54 by cboussau         ###   ########.fr       */
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

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "USER") == 0)
		{
			color(BLUE, "# ");
			color(RESET, "");
			color(CYAN, node->user);
			color(RESET, "");
		}
		node = node->next;
	}
	ft_putstr(" in ");
	node = tmp;
}

static int	cmp_pwd_home(t_lst *node, char *buff)
{
	t_lst *tmp;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "HOME") == 0)
			if (ft_strcmp(node->home, buff) == 0)
				return (1);
		node = node->next;
	}
	node = tmp;
	return (0);
}

static void	prompt_path(t_lst *node)
{
	t_lst	*tmp;
	char	buff[100];
	char	*str;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "PWD") == 0)
		{
			getcwd(buff, 100);
			node->line = ft_strjoin("PWD=", buff);
			node = tmp;
			if (cmp_pwd_home(node, buff) == 0)
			{	
				str = ft_strrchr(buff, '/');
				color(PURPLE, str);
				color(RESET, "");
			}
			return ;
		}
		node = node->next;
	}
	node = tmp;
}

void		get_prompt(t_lst *node)
{
	prompt_name(node);
	color(PURPLE, "");
	ft_putchar('~');
	color(RESET, "");
	prompt_path(node);
	color(RED, " \n$> ");
	color(RESET, "");
}
