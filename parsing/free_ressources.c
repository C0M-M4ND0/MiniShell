/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:08 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:09 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_2d(char	**strs)
{
	int	i;

	i = -1;
	while (strs && strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
	strs = NULL;
}

void	exit_error(t_collect *var, char *short_cmd, char *msg, int exit_code)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(short_cmd, STDERR_FILENO);
	if (!msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	free_res(var);
	free(short_cmd);
	exit (exit_code);
}

void	free_res(t_collect *var)
{
	free_2d(var->cmd);
	free_2d(var->paths);
	free(var->slash_cmd);
	var->slash_cmd = NULL;
}
