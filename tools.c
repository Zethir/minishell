/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:17:58 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/31 22:34:24 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strccmp(const char *s1, const char *s2, char c)
{
	unsigned char *tmp1;
	unsigned char *tmp2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (*tmp1 && *tmp1 == *tmp2 && *tmp1 != c)
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}

int		ft_strlen_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	deal_with_prompt_path(int i, char *buff)
{
	char	*str;

	if (i >= 1)
	{
		color(PURPLE, "");
		ft_putchar('~');
		color(RESET, "");
	}
	if (i > 1)
	{
		str = ft_strdup(&buff[i]);
		color(PURPLE, str);
		color(RESET, "");
	}
	else if (i == 0)
	{
		str = ft_strchr(buff, '/');
		color(PURPLE, str);
		color(RESET, "");
	}
}

int		get_index(t_lst *node)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = node;
	while (node)
	{
		i++;
		node = node->next;
	}
	node = tmp;
	return (i);
}

void	exec_right_path(t_lst *node, char **arg, char **env, char *right_path)
{
	right_path = ft_strjoin(right_path, "/");
	check_command(node, arg, right_path, env);
	ft_strdel(env);
}
