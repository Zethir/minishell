/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:06:02 by cboussau          #+#    #+#             */
/*   Updated: 2016/04/04 21:01:33 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_lst(t_lst *node)
{
	t_lst	*tmp;

	tmp = node;
	while (node)
	{
		if (node->line)
			return (1);
		else
			node = node->next;
	}
	node = tmp;
	return (0);
}

int		check_caract(char *str, char c)
{
	int		i;

	i = 0;
	if (str[i] == c)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_lst	*delete_elem(t_lst *node)
{
	t_lst	*tmp;
	t_lst	*tmp2;

	tmp = node;
	tmp2 = node;
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
	{
		free(node);
		return (NULL);
	}
	while (tmp->next != NULL)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = NULL;
	return (node);
}

void	add_elem(t_lst *node, char *arg)
{
	t_lst	*new_elem;

	new_elem = (t_lst *)malloc(sizeof(t_lst));
	new_elem->next = NULL;
	new_elem->line = ft_strdup(arg);
	new_elem->name = ft_strsub(arg, 0, ft_strlen_char(arg, '='));
	push_node(new_elem, &node);
}

char	**malloc_tab(int i)
{
	char **save;

	save = (char **)malloc(sizeof(char *) * i + 1);
	if (!save)
		return (NULL);
	return (save);
}
