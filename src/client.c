/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:09 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/26 02:33:31 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		else
			sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (sign * number);
}

/*
** handle_error - handle error when argc != 3
*/

void	handle_error(void)
{
	write(1, "usage: ./client [server-pid] [message]\n", 39);
	exit(EXIT_FAILURE);
}

/*
** send_bits - function that send the message to the server (ascii -> 8bits)
** @pid: id of process
** @msg: msg to send
*/

int	send_bits(int pid, char *msg)
{
	int	bitmask;
	int	i;

	bitmask = -1;
	i = 0;
	while (msg[i])
	{
		while (++bitmask < 8)
		{
			if (msg[i] & 0x80 >> bitmask)
				printf("1");
			else
				printf("0");
			usleep(3);
		}
		i++;
	}
	printf("\n");
	return (0);
}

/*
** handle_client_signal - function that handle each case of signal
** @sig: SIGUSR1 or SIGUSR2
*/

void	handle_client_signal(int sig)
{
	if (sig == SIGUSR1)
	{
		write (STDOUT_FILENO, "Message send succesfully :)\n", 28);
		exit (EXIT_SUCCESS);
	}
	else if (sig == SIGUSR2)
	{
		write (STDERR_FILENO, "Server conexion error :(!\n", 26);
		exit (EXIT_FAILURE);
	}
}

/*
** main - point of start the client program
*/

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		handle_error();
	signal(SIGUSR1, handle_client_signal);
	signal(SIGUSR2, handle_client_signal);
	pid = ft_atoi(argv[1]);
	send_bits(pid, argv[2]);
	while (1)
		pause();
}
