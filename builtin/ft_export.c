/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:05:39 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:13:22 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_print_envp(char **envp)
{
	int		i;
	int		j;
	int		index;
	char	**hol;

	i = 0;
	while (envp[i])
		i++;
	hol = (char **)malloc(sizeof(char *) * (i + 1));
	if (!hol)
		return ;
	hol[i] = NULL;
	i = 0;
	while (envp[i])
	{
		j = -1;
		index = 0;
		while (envp[++j])
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
				index++;
		hol[index] = envp[i];
		i++;
	}
	print_envp(hol);
}

int	check_val_quotes(char *str)
{
	int	i;

	i = 0;
	if (check_num_arg(str[0], EXP_ARG))
		return (g_vars.exit_code = 1, 1);
	while (str[i] && str[0] != '=' && (ft_isalnum(str[i])
			|| str[i] == '=' || str[i] == '+' || str[i] == '_'))
	{
		if (str[i] == '\'' || str[i] == '"'
			|| (str[i] == '+' && str[i + 1] != '='))
		{
			ft_putendl_fd(EXP_ARG, STDERR_FILENO);
			return (g_vars.exit_code = 1, 1);
		}
		if (str[i] == '=')
			return (0);
		i++;
	}
	if (str[i] && (str[0] == '=' || !ft_isalnum(str[i])))
	{
		ft_putendl_fd(EXP_ARG, STDERR_FILENO);
		g_vars.exit_code = 1;
	}
	return (1);
}

int	extract_var(char **var, bool *plus)
{
	int	i;
	int	len;

	i = 0;
	(*plus) = 0;
	while (var[0] && var[0][i] && var[0][i] != '=')
		i++;
	len = i + 1;
	if (var[0] && var[0][i - 1] == '+' && ++(*plus))
	{
		while (--i > 0)
			var[0][i] = var[0][i - 1];
		var[0] = &var[0][1];
	}
	return (len);
}

int	update_envp(char *var, char **envp)
{
	int		i;
	int		len;
	char	*hol;
	char	*name;
	bool	plus;

	name = ft_strdup(var);
	len = extract_var(&name, &plus);
	name[len - plus] = '\0';
	i = 0;
	while (envp[i])
	{
		hol = ft_strnstr(envp[i], name, len - plus);
		if (hol)
		{
			free(envp[i]);
			if (plus)
				envp[i] = ft_strjoin(envp[i], &var[len]);
			else
				envp[i] = ft_strdup(var);
			return (free((name - plus)), 1);
		}
		i++;
	}
	return (free((name - plus)), 0);
}

void	ft_export(char **args, char **envp)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!args[0])
		return (export_print_envp(envp));
	while (envp[j])
		j++;
	while (args[i])
	{
		if (!check_val_quotes(args[i]))
		{
			if (!update_envp(args[i], envp))
			{
				check_plus(&args[i]);
				free(envp[j]);
				envp[j] = ft_strdup(args[i]);
				envp[j + 1] = NULL;
				j++;
			}
		}
		i++;
	}
}
