/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:05:39 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:13:22 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_envp(char *envp)
{
	int		i;
	bool	one;

	i = 0;
	one = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		ft_putchar_fd(envp[i], STDOUT_FILENO);
		if (!one && envp[i] == '=')
		{
			ft_putchar_fd('"', STDOUT_FILENO);
			one = 1;
		}
		i++;
	}
	ft_putendl_fd("\"", STDOUT_FILENO);
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		put_envp(envp[i]);
		i++;
	}
}

void	check_plus(char **var)
{
	int		i;
	char	*hol;

	i = 0;
	while (var[0] && var[0][i] && var[0][i] != '=')
		i++;
	if (var[0] && var[0][i - 1] == '+')
	{
		while (--i > 0)
			var[0][i] = var[0][i - 1];
		hol = ft_strdup(&var[0][1]);
		free(var[0]);
		var[0] = hol;
	}
}
