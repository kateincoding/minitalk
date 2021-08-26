/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:17 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/26 02:35:27 by ksoto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

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

	if (sig == SIGUSR1)
	{
		write (1, "0", 1);
		c ^= 0x80 >> bits;
	}
	else if (sig == SIGUSR2)
	{
		write (1, "1", 1);
		c |= 0x80 >> bits;
	}
	bits++;
	if (bits == 8)
	{
		printf ("-> %c\n", c);
		bits = 0;
		c = 0xFF;
	}
}

/*
** main - point of start the client program
*/

int	main(void)
{
	struct sigaction	sa;
	sigset_t			non_mask;
	pid_t				pid;

	pid = getpid();
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = non_mask;
	sa.sa_sigaction = receive_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// write(1, "PID: ", 5);
	printf("PID: %d\n", pid);
	// ft_putnbr_fd(getpid(), 1);
	// write(1, "\n", 1);
	while (1)
		pause();
}
