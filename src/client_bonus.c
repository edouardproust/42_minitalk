/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/08 16:18:32 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_flag = 0;

static void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_ack_flag = 1;
	else if (signal == SIGUSR2)
		g_ack_flag = 2;
}

static void	send_message(int server_pid, char *msg, size_t len)
{
	size_t	i;
	int		j;
	int		signal;

	i = -1;
	while (++i <= len)
	{
		j = -1;
		while (++j < 8)
		{
			signal = SIGUSR1;
			if ((msg[i] >> j) & 1)
				signal = SIGUSR2;
			if (kill(server_pid, signal) == -1)
				ft_error("Failed to send bit to server\n");
			while (g_ack_flag == 0)
				pause();
			if (g_ack_flag == 1)
				g_ack_flag = 0;
		}
	}
	while (g_ack_flag != 2)
		pause();
	ft_putstr_fd("Message received by server.\n", STDOUT_FILENO);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	if (ac != 3)
		ft_error("Usage: ./client_bonus <server PID> <message>\n");
	server_pid = ft_atoi(av[1]);
	if (server_pid == 0 || server_pid == -1)
		ft_error("Incorrect server PID\n");
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Failed to set client's signal handler\n");
	send_message(server_pid, av[2], ft_strlen(av[2]));
	return (EXIT_SUCCESS);
}
