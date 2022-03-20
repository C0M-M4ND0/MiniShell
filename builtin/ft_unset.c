/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:06:16 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:15:38 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_envp(char *var, char **envp)
{
	int		i;
	char	*hol;

	i = 0;
	while (envp[i])
	{
		hol = ft_strnstr(envp[i], var, ft_strlen(var));
		if (hol && envp[i][ft_strlen(var)] == '=')
		{
			free(envp[i]);
			while (envp[i])
			{
				envp[i] = envp[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int	check_val_identiers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_putendl_fd(UNSET_ARG, STDERR_FILENO);
			return (g_vars.exit_code = 1, 1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(char **args, char **envp)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!check_val_identiers(args[i])
			&& !check_num_arg(args[i][0], UNSET_ARG))
			unset_envp(args[i], envp);
		i++;
	}
}
