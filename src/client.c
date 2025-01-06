/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/06 17:29:21 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int	send_message(int server_pid, char *msg)
{
	size_t len;
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
			signal = (msg[i] >> (7 - j)) & 1;
			ft_printf("%d", signal);
			if (signal == 0)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;	
			if (kill(server_pid, signal) == -1)
				return (0);
			usleep(100);
		}
	}
	return (1);
}

int	main(int ac, char **av)
{
	int			server_pid;

	if (ac != 3)
		return (ft_printf("Usage: ./client <server PID> <message>\n"), 1);
	server_pid = ft_atoi(av[1]);
	if (!server_pid)
		return (ft_printf("Error\n"), 1);
	// TODO: More checks on args here?
	if (!send_message(server_pid, av[2]))
		return (ft_printf("Error: Failed to send message\n"), 1);
	return (0);
}
