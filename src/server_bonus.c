/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/08 15:30:36 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit_count = 0;

	(void)context;
	if (signal == SIGUSR1)
		c |= 0 << bit_count;
	else if (signal == SIGUSR2)
		c |= 1 << bit_count;
	bit_count++;
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("Failed to send bit confirmation to client\n");
	if (bit_count == 8)
	{
		if (c == 0)
		{
			c = '\n';
			usleep(100);
			if (kill(info->si_pid, SIGUSR2) == -1)
				ft_error("Failed to send message confirmation to client\n");
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Failed to set server's sigaction\n");
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
