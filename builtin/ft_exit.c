/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:05:10 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:10:00 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
}

void	exit_minish_ctrl_d(char **envp)
{
	if (tgetstr("cm", NULL))
		ft_putendl_fd("\033[1A\033[9Cexit", STDOUT_FILENO);
	else
		ft_putendl_fd("exit", STDOUT_FILENO);
	free_envp(envp);
	exit(0);
}

void	ft_exit(char **args, char **envp)
{
	int	j;

	j = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	while (args && args[0] && args[0][j])
	{
		if (args[0][j] == '-' || args[0][j] == '+')
			j++;
		if (!ft_isdigit(args[0][j]))
			return (g_vars.exit_shell = 255, free_envp(envp),
				ft_putendl_fd(ERR_EXIT_ARG, STDERR_FILENO));
		j++;
	}
	if (args && args[0] && args[1])
		return (g_vars.exit_code = 1, ft_putendl_fd(ERR_EXIT_NUM, 2));
	g_vars.exit_shell = ((unsigned char)ft_atoi(args[0]));
}
