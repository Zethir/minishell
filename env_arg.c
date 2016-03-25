/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 18:45:03 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/25 19:43:20 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(t_lst *node, char *arg);
{
	t_lst *tmp;

	tmp = node;
	while (node)
	{
		if (ft_strncmp(node->line, arg, ft_strlen(arg)) == 0)
		{
			arg = ft_strsub(arg, 0, ft_strlen(arg) - 1);
			


void		deal_with_opt(t_lst *node, char *line)
{
	char	**arg;

	arg = ft_strsplit(&line[4], ' ');
	while (*arg)
	{
		if (*arg == '-' && *arg[1] == 'u')
		{
			arg++;
			check_arg(node, *arg);
		}
