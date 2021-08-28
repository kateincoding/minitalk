/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:17 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/27 22:05:39 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(int pid, char *str)
{
	if (str)
		free(str);
	write(STDERR_FILENO, "Unexpected error\n", 17);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

/*
** print_msg - function that print a message
** @msg: message to send
** return: void
*/

void	print_msg(char *msg)
{
	ft_putstr_fd(msg, 1);
	free(msg);
}

/*
** receive_signal - function that handle each case of signal
** @sig: SIGUSR1 or SIGUSR2
** @info: The siginfo_t structure is passed as the second parameter 
** to a user signal handler function, if the SA_SIGINFO flag was 
** specified when the handler was installed with sigaction().
** @other: 
*/

void	receive_signal(int sig, siginfo_t *info, void *other)
{
	static char	c = 0xFF;
	static int	bits = 0;
	static char	*msg = 0;

	(void)other;
	if (sig == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (sig == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
			msg = ft_append(msg, c);
		else
			print_msg(msg);
		bits = 0;
		c = 0xFF;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		error(info->si_pid, msg);
}

/*
** main - point of start the client program
** Functions election:
** sigaction instead of signal to access to the pid of
** the sender: client 'info->si_pid'
** infinite pause() loop waiting for signals from client
*/

int	main(void)
{
	struct sigaction	sa;
	sigset_t			non_mask;

	sigemptyset(&non_mask);
	sigaddset(&non_mask, SIGINT);
	sigaddset(&non_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = non_mask;
	sa.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
}
