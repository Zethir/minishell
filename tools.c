/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:17:58 by cboussau          #+#    #+#             */
/*   Updated: 2016/03/27 16:53:05 by cboussau         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
