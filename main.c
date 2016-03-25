/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:38:13 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/24 18:54:12 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_node(t_lst *node, t_lst **head)
{
	t_lst	*tmp;


	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	else
		tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_lst	*init_lst(char **env)
{	
	t_lst	*node;
	t_lst	*head;

	head = NULL;
	while (*env)
	{
		node = (t_lst *)malloc(sizeof(t_lst));
		if (!node)
			return (NULL);
		node->next = NULL;
		node->line = ft_strdup(*env);
		push_node(node, &head);
		env++;
	}
	return (head);
}

static void		main_minishell(t_lst *node)
{
	get_prompt(node);
}

int		main(int ac, char **av, char **env)
{
	t_lst	*node;
	
	av = NULL;
	node = init_lst(env);
	signal(SIGINT, SIG_IGN);
	if (ac == 1)
		main_minishell(node);
	else
		return (1);	
	return (0);
}
