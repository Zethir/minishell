/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:48:35 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 21:13:28 by cboussau         ###   ########.fr       */
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

static void	prompt_path(t_lst *node)
{
	t_lst	*tmp;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "PWD") == 0)
		{
			color(PURPLE, "");
			ft_putchar('~');
			color(RESET, "");
			color(PURPLE, node->path);
			color(RESET, "");
		}
		node = node->next;
	}
	color(RED, " \n$> ");
	color(RESET, "");
	node = tmp;
}

void		get_prompt(t_lst *node)
{
	prompt_name(node);
	prompt_path(node);
}
