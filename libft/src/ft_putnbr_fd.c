/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 08:28:55 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/27 20:36:08 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putint(int nb, int fd)
{
	if (nb > 9)
		ft_putint(nb / 10, fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}

static void	ft_putnint(unsigned int n, int fd)
{
	if (n > 9)
		ft_putnint(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
		ft_putnint(nb, fd);
	}
	else
		ft_putint(n, fd);
}
