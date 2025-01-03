/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/03 16:53:31 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int	set_signals(sigset_t *sigset, char *msg)
{
	int	msglen;
	int	siglen;
	int	i;
	int j;

	msglen = ft_strlen(msg);
	siglen = 0;
	i = 0;
	while (i < msglen)
	{
		j = 0;
		while (j < 8)
		{
			sigset[siglen] = (c >> (7 - i)) & 1;
			j++;
			siglen++;
		}
		i++;
	}
	return (siglen);
}

static int	send_sigset(int pid, sigset_t sigset, int siglen)
{
	int	i;
	int	signal;

	i = 0;
	while (i < siglen)
	{
		signal = SIGUSR1;
		if (sigset[i] == 1)
			signal = SIGUSR2;
		if (kill(pid, SIGUSR2) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int			pid;
	int			msg_sent;
	sigset_t	sigset;
	int			siglen;

	if (ac != 3)
		return (ft_printf("Usage: ./client <server PID> <message>\n"), 1);
	pid = ft_atoi(av[1]);
	if (!pid)
		return (ft_printf("Error\n"), 1);
	// TODO: More checks on args here?
	sigemptyset(&sigset);
	siglen = fill_sigset(&sigset, av[2]);
	if (siglen == 0)	
		return (ft_printf("Error\n"), 1);
	if (!send_sigset(pid, sigset, siglen))
		return (ft_printf("Error: Failed to send message\n"), 1);
	return (0);
}
