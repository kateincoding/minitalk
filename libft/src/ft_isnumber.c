/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 13:02:30 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/27 16:02:25 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_isnumber - function that check if nbr is a number
** @nbr: number in string format
** @Return: 1 if it is true, otherwise 0
*/

int	ft_isnumber(char *nbr)
{
	int	i;

	i = 0;
	if (nbr[i] == '-')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}
