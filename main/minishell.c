/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:08:45 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:08:47 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_shlvl(char **envp)
{
	int		i;
	int		shlvl;
	char	*hol;
	char	*shlvl_str;

	i = 0;
	while (envp && envp[i])
	{
		envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shlvl = ft_atoi(ft_getenv("SHLVL=", envp));
	hol = ft_itoa(shlvl + 1);
	shlvl_str = ft_strjoin("SHLVL=", hol);
	free (hol);
	update_envp(shlvl_str, envp);
	free(shlvl_str);
}

int	main(int ac, char **av, char **envp)
{
	update_shlvl(envp);
	g_vars.exit_shell = 257;
	display_prompt("minish_$ ", envp);
	(void)ac;
	(void)av;
	return (0);
}
