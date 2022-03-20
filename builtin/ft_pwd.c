/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:06:01 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:15:05 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **args)
{
	char	buff[PATH_MAX];
	int		i;

	i = 0;
	(void)args;
	if (getcwd(buff, sizeof(buff)) == NULL)
		return (g_vars.exit_code = 1, ft_putstr_fd("minish: pwd: ", 2),
			ft_putstr_fd(args[0], STDERR_FILENO), perror(" \b"));
	else
		ft_putendl_fd(buff, STDOUT_FILENO);
}
