/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaltint@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 19:14:22 by kaaltint          #+#    #+#             */
/*   Updated: 2026/11/19 19:16:32 by kaaltint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_has_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	gnl_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_join(char *str1, char *str2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(gnl_strlen(str1) + gnl_strlen(str2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str1 && str1[i])
	{
		new[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
	{
		new[i + j] = str2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}
