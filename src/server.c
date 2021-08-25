/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 07:34:17 by kate              #+#    #+#             */
/*   Updated: 2021/08/25 15:40:49 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void minitalk_handler(int sig)
{
    write(STDOUT_FILENO,"I will not die!\n", 16);
}

int main(void)
{
//    signal(SIGINT, &minitalk_handler);

    struct sigaction    sa;
    sigset_t            non_mask;

    sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = non_mask;
	sa.sa_sigaction = minitalk_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    while(1)
    {
        printf("hiiiii goku %d\n", getpid());
        sleep(2);
    }
    return 0;
}
