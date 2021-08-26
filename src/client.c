/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:09 by kate              #+#    #+#             */
/*   Updated: 2021/08/25 23:55:05 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	handle_error(void)
{
	write(1, "usage: ./client [server-pid] [message]\n", 39);
	exit(EXIT_FAILURE);
}

/*
** send_bits - function that send the message to the server bit per bit
** @pid: id of process
** @msg: msg to send
*/

int	send_bits(int pid, char *msg)
{
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
	if (argc != 3)
		handle_error();
	signal(SIGUSR1, handle_client_signal);
	signal(SIGUSR2, handle_client_signal);
	send_bits(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
