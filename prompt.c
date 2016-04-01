/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 17:48:35 by cboussau          #+#    #+#             */
/*   Updated: 2016/04/01 18:19:20 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		color(char *color, char *str)
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
	t_lst	*tmp;
	int		i;

	tmp = node;
	i = 0;
	while (node)
	{
		if (ft_strcmp(node->name, "HOME") == 0)
		{
			if (ft_strcmp(node->home, buff) == 0)
				return (1);
			else if (ft_strncmp(node->home, buff, 20) == 0)
			{
				i = ft_strlen(node->home);
				return (i);
			}
		}
		node = node->next;
	}
	node = tmp;
	return (0);
}

static void	prompt_path(t_lst *node)
{
	t_lst	*tmp;
	char	buff[100];
	int		i;

	tmp = node;
	while (node)
	{
		if (ft_strcmp(node->name, "PWD") == 0)
		{
			getcwd(buff, 100);
			node = tmp;
			i = cmp_pwd_home(node, buff);
			deal_with_prompt_path(i, buff);
			return ;
		}
		node = node->next;
	}
	node = tmp;
}

void		get_prompt(t_lst *node)
{
	color(BLUE, "# ");
	color(RESET, "");
	prompt_name(node);
	prompt_path(node);
	color(RED, " \n$> ");
	color(RESET, "");
}
