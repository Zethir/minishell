/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 17:27:17 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/28 21:21:13 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_opt(char *arg)
{
	ft_putstr("env: unsetenv ");
	ft_putstr(arg);
	ft_putstr(": Invalid argument\n");
}

void	print_error_arg(void)
{
	ft_putendl("env: missing argument after option");
	ft_putstr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
	ft_putstr("           [name=value ...] [utility [argument ...]]\n");
}	

int		print_alpha_error(char **arg)
{
	int 	i;
	char	*error;
	
	i = 0;
	error = "setenv: Variable name must contain alphanumeric characters.";
	while (arg[0][i])
	{
		if (arg[0][i] == '=')
		{
			ft_putendl(error);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_env_error(char *arg)
{
	ft_putstr("env: ");
	ft_putstr(arg);
	ft_putendl(": No such file or directory");
}

int		no_command_error(char *arg)
{
	ft_putstr(arg);
	ft_putendl(": Command not found.");
	return (-1);
}

void	print_main_error(char *arg)
{
	ft_putstr("env: illegal option -- ");
	ft_putendl(arg);
	ft_putstr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
	ft_putstr("           [name=value ...] [utility [argument ...]]\n");
}

