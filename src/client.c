/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/07 18:59:08 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_server_confirmation;

static void	signal_handler(int signal)
{
	(void)signal;
	g_server_confirmation = 1;
}

static	int	send_message(int server_pid, char *msg)
{
	size_t	len;
	size_t	i;
	int		j;
	int		bit;

	len = ft_strlen(msg);
	i = -1;
	while (++i <= len)
	{
		j = -1;
		while (++j < 8)
		{
			bit = (msg[i] >> j) & 1;
			if (bit == 0)
				bit = SIGUSR1;
			else
				bit = SIGUSR2;
			if (kill(server_pid, bit) == -1)
				return (0);
			while (!g_server_confirmation)
				pause();
			g_server_confirmation = 0;
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	if (ac != 3)
		return (ft_printf("Usage: ./client <server PID> <message>\n"),
			EXIT_FAILURE);
	server_pid = ft_atoi(av[1]);
	if (!server_pid)
		return (ft_printf("Error\n"), 1);
	g_server_confirmation = 0;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (ft_printf("Error: failed to set signal handler\n"),
			EXIT_FAILURE);
	if (!send_message(server_pid, av[2]))
		return (ft_printf("Error: Failed to send message\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
