/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:09 by ksoto             #+#    #+#             */
/*   Updated: 2021/09/01 22:13:32 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/*
** handle_error - handle error when argc != 3
*/

void	handle_error(int type, char *str)
{
	if (type == 1)
	{
		write(2, "[Format Error]: ./client <PID> <message>\n", 41);
		exit(EXIT_FAILURE);
	}
	else if (type == 2)
	{
		if (str)
			free(str);
		write(2, "[Error]: we couldn't send your message :'c\n", 43);
		exit(EXIT_FAILURE);
	}
}

/*
** send_null_char - send the null character "\0" = 0000 0000
** it will be sended when all the message already was sent
** @st_pid: pid to send
** message to free
*/

int	send_null_char(int pid, char *message)
{
	static int	idx = 0;

	if (idx++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error(2, message);
		return (0);
	}
	return (1);
}

/*
** send_bits_bits - function that send the message to the server (ascii -> 8bits)
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

int	send_bits_bits(int pid, char *str)
{
	static char	*msg_to_send = 0;
	static int	stc_pid = 0;
	static int	bit = -1;

	if (str)
		msg_to_send = ft_strdup(str);
	if (!msg_to_send)
		handle_error(2, 0);
	if (pid)
		stc_pid = pid;
	if (msg_to_send[++bit / 8])
	{
		if (msg_to_send[bit / 8] & (0x80 >> (bit % 8)))
		{
			if (kill(stc_pid, SIGUSR2) == -1)
				handle_error(2, msg_to_send);
		}
		else if (kill(stc_pid, SIGUSR1) == -1)
			handle_error(2, msg_to_send);
		return (0);
	}
	if (!send_null_char(stc_pid, msg_to_send))
		return (0);
	free(msg_to_send);
	return (1);
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
		finish = send_bits_bits(0, 0);
	else if (sig == SIGUSR2)
	{
		write (STDERR_FILENO, "[Error] Bad conexion with the server :(!\n", 53);
		exit(EXIT_FAILURE);
	}
	if (finish)
	{
		write (STDOUT_FILENO, "[Success] Message send succesfully :)\n", 38);
		exit(EXIT_SUCCESS);
	}
}

/*
** main - point of start the client program
** @argc: number of args
** @argv: arguments
*/

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !ft_isnumber(argv[1]))
		handle_error(1, NULL);
	signal(SIGUSR1, handle_client_signal);
	signal(SIGUSR2, handle_client_signal);
	pid = ft_atoi(argv[1]);
	send_bits_bits(pid, argv[2]);
	while (1)
		pause();
}
