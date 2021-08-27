/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:09 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/27 11:34:43 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
** handle_error - handle error when argc != 3
*/

void	handle_error(int type)
{
	if (type == 1)
	{
		write(2, "usage: ./client [server-pid] [message]\n", 39);
		exit(EXIT_FAILURE);
	}
	else if (type == 2)
	{
		write(2, "Error sending message\n", 22);
		exit(EXIT_FAILURE);
	}
}

/*
** send_null_char - send the null character "\0" = 0000 0000
** it will be sended when all the message already was sent
** @st_pid: pid to send
** message to free
*/

int	send_null_char(int st_pid, char *message)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(st_pid, SIGUSR1) == -1)
			free(message), handle_error(2);
		return (0);
	}
	return (1);
}

/*
** send_bits - function that send the message to the server (ascii -> 8bits)
** @pid: id of process
** @msg: msg to send
** static variables:
** *message: It's a duplicate string given in the main() fx of client to send to
** server. This variable has to be constant in replace of a global 
** variable in order for the client to send a bit every time sent_bits is called
** The message is passed bit per bit in order all the message is send it, that's
** why instead of a while(msg[i]). It's replaced by "if" and static variables
** st_pid: static pid
*/

int	send_bits(int pid, char *msg)
{
	static int		bitmask = -1;
	static char		*message = 0;
	static int		st_pid;

	if (msg)
		message = ft_strdup(msg);
	if (!message)
		free(0), handle_error(2);
	if (pid)
		st_pid = pid;
	if (msg[++bitmask / 8])
	{
		if (msg[bitmask / 8] & (0x80 >> (bitmask % 8)))
			if (kill(pid, SIGUSR2) == -1)
				free(msg), handle_error(2);
		else if (kill(pid, SIGUSR1) == -1)
			free(msg), handle_error(2);
		return (0);
	}
	if (!send_null_char(st_pid, message))
		return (0);
	free (message);
	return (0);
}

/*
** handle_client_signal - function that handle each case of signal
** @sig: SIGUSR1 or SIGUSR2
*/

void	handle_client_signal(int sig)
{
	int	finish;

	finish = 0;
	if (sig == SIGUSR1)
		finish = send_bit(0, 0);
	if (sig == SIGUSR2)
	{
		write (STDERR_FILENO, "Server conexion error :(!\n", 26);
		exit (EXIT_FAILURE);
	}
	if (finish)
	{
		write (STDOUT_FILENO, "Message send succesfully :)\n", 28);
		exit (EXIT_SUCCESS);
	}
}

/*
** main - point of start the client program
*/

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		handle_error(1);
	signal(SIGUSR1, handle_client_signal);
	signal(SIGUSR2, handle_client_signal);
	pid = ft_atoi(argv[1]);
	send_bits(pid, argv[2]);
	while (1)
		pause();
}
