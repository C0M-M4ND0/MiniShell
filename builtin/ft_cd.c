/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:03:59 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 15:06:28 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *var, char **envp)
{
	int		i;
	char	*hol;

	i = 0;
	while (envp[i])
	{
		hol = ft_strnstr(envp[i], var, ft_strlen(var));
		if (hol)
			return (&hol[ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

void	change_var(char *new, char *var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
		{
			free(envp[i]);
			envp[i] = new;
			break ;
		}
		i++;
	}
}

void	cd_empty_args(char **envp)
{
	if (chdir(ft_getenv("HOME=", envp)) == -1)
		return (g_vars.exit_code = 1, perror("minish: cd"));
}

void	ft_cd(char **args, char **envp)
{
	char	temp[PATH_MAX];
	char	*new_opwd;
	char	*cur_opwd;

	if (!getcwd(temp, sizeof(temp)))
		return (g_vars.exit_code = 1, perror("minish: getcwd"));
	if (!args[0])
		cd_empty_args(envp);
	else if (!ft_strncmp(args[0], "-", 1) && ft_strlen(args[0]) == 1)
	{
		cur_opwd = ft_getenv("OLDPWD=", envp);
		if (!cur_opwd)
			return (g_vars.exit_code = 1, ft_putstr_fd("\n", STDOUT_FILENO));
		if (chdir(cur_opwd) == -1)
			return (g_vars.exit_code = 1, perror("minish: cd"));
		ft_putendl_fd(cur_opwd, STDOUT_FILENO);
	}
	else if (chdir(args[0]) == -1)
		return (ft_putstr_fd("minish: cd: ", STDERR_FILENO),
			ft_putstr_fd(args[0], STDERR_FILENO), perror(" \b"));
	new_opwd = ft_strjoin("OLDPWD=", temp);
	change_var(new_opwd, "OLDPWD=", envp);
	if (getcwd(temp, sizeof(temp)))
		change_var(ft_strjoin("PWD=", temp), "PWD=", envp);
}
