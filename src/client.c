/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/08 15:56:28 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_bit_received = 0;

static void	signal_handler(int signal)
{
	(void)signal;
	g_bit_received = 1;
}

static void	send_message(int server_pid, char *msg)
{
	size_t	len;
	size_t	i;
	int		j;
	int		signal;

	len = ft_strlen(msg);
	i = -1;
	while (++i <= len)
	{
		j = -1;
		while (++j < 8)
		{
			if ((msg[i] >> j) & 1)
				signal = SIGUSR2;
			else
				signal = SIGUSR1;
			if (kill(server_pid, signal) == -1)
				ft_error("Failed to send bit to server\n");
			while (!g_bit_received)
				pause();
			g_bit_received = 0;
		}
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	if (ac != 3)
		ft_error("Usage: ./client <server PID> <message>\n");
	server_pid = ft_atoi(av[1]);
	if (server_pid == 0 || server_pid == -1)
		ft_error("Incorrect server PID\n");
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error("Failed to set client's signal handler\n");
	send_message(server_pid, av[2]);
	return (EXIT_SUCCESS);
}
