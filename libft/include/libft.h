/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:52:12 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/30 00:20:41 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>

int		ft_atoi(const char *str);
char	*ft_append(char *str, char c);
int		ft_isdigit(int c);
int		ft_isnumber(char *nbr);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

/*
**	stdio
*/

int		ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(const char *s, int fd);

#endif