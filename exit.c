/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:11:24 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 17:25:40 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_with_int(char **arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] < '0' || (*arg)[i] > '9')
		{	
			ft_putendl("exit: Badly formed number.");
			return (-1);
		}
		i++;
	}
	return (0);
}
	
int			do_exit(char *line)
{
	int 	i;
	char	**arg;

	i = 0;
	arg = ft_strsplit(&line[5], ' ');
	if (!*arg)
		return (0);
	while (arg[i])
		i++;
	if (i > 1)
	{
		ft_putendl("exit: Expression Syntax.");
		return (-1);
	}
	if (*arg[0] >= '0' && *arg[0] <= '9')
	{
		if (deal_with_int(arg) == 0)
			i = ft_atoi(*arg);
		else
			return (-1);
	}
	return (i);
}
