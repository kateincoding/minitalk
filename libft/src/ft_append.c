/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 13:02:13 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/29 21:59:37 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** allocate_memory_first - allocate memory when a str is empty or not
** @c: char to append at the final of string
*/

char	*allocate_memory_first(char c)
{
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * 2);
	if (!new_str)
		return (NULL);
	new_str[0] = c;
	new_str[1] = '\0';
	return (new_str);
}

/*
** ft_append - function to append a char c at the final of a string *str
** @str: string that we need to append a char at the final
** @c: char to append at the final of string
*/

char	*ft_append(char *str, char c)
{
	char	*new_str;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (allocate_memory_first(c));
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new_str)
		return (free(str), NULL);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	free(str);
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}
