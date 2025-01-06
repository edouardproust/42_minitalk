/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:49:34 by eproust           #+#    #+#             */
/*   Updated: 2025/01/06 18:12:18 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_signals = NULL;

void	signal_handler(int signal)
{
	char	append[2];

	if (signal == SIGUSR1)
		append[0] = 0 + '0';
	else
		append[0] = 1 + '0';
	append[1] = 0;
	g_signals = ft_strjoin(g_signals, append);
	if (!g_signals)
	{
		ft_printf("Error"); // TODO
		return ;
	}
	//ft_printf("%s\n", g_signals);
}

int	main(void)
{
	size_t	len;

	ft_printf("Server PID: %d\n", getpid());
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Error"), 1); // TODO
	while (1)
	{
		pause();
		len = ft_strlen(g_signals);
		if (len > 7 && ft_strncmp(g_signals + (len - 8), "00000000", 8) == 0)
			ft_printf("%s\n", g_signals);
	}
	return (0);
}
