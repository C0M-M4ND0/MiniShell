/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_symbol.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:07:42 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:07:44 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_symbol(char c, int o_quote)
{
	if ((o_quote % 2) && c == '"')
		return (1);
	if (!c || c == '%' || c == '^' || c == '#' || c == '+' || c == '/'
		|| c == '-' || c == '~' || c == '=' || c == ':' || c == ' ')
		return (1);
	return (0);
}

void	protect_expanded_name_quotes(char **exp_name)
{
	char	*hol;
	char	quote[2];
	int		i;

	if (!exp_name[0] || !exp_name[0][0])
		return ;
	i = 0;
	quote[1] = '\0';
	quote[0] = '"';
	while (exp_name[0] && exp_name[0][i]
		&& exp_name[0][i] != '\'' && exp_name[0][i] != '"')
		i++;
	if (exp_name[0][i] == '"')
		quote[0] = '\'';
	hol = exp_name[0];
	exp_name[0] = ft_strjoin(quote, exp_name[0]);
	free(hol);
	hol = exp_name[0];
	exp_name[0] = ft_strjoin(exp_name[0], quote);
	free(hol);
}

int	get_l_char_env(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalnum(str[i]))
		return (1);
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

char	*get_env_var(char *str, char **envp)
{
	int		last;
	char	*hol;
	char	*name;
	char	*exp_name;
	char	*expanded;

	last = 0;
	hol = NULL;
	name = NULL;
	if (str[0] == '?' && ++last)
		exp_name = ft_itoa(g_vars.exit_code);
	else
	{
		last = get_l_char_env(str);
		hol = ft_substr(str, 0, last);
		name = ft_strjoin(hol, "=");
		exp_name = ft_strdup((ft_getenv(name, envp)));
		protect_expanded_name_quotes(&exp_name);
		free(hol);
		hol = NULL;
	}
	if (last != (int)ft_strlen(str))
		hol = &str[last];
	expanded = ft_strjoin(exp_name, hol);
	return (free(name), free(exp_name), expanded);
}

char	*expand_dollar_symbol(char *line, char **envp)
{
	int		i;
	int		o_quote;
	char	*hol;
	char	*env_var;

	i = -1;
	o_quote = 0;
	while (line && line[++i])
	{
		if (line[i] == '"')
			o_quote++;
		if (!(o_quote % 2))
			i += check_single_quotes(&line[i]);
		if (line && line[i] == '$' && !valid_symbol(line[i + 1], o_quote))
		{
			line[i--] = '\0';
			env_var = get_env_var(&line[i + 2], envp);
			hol = ft_strjoin(&line[0], env_var);
			free(env_var);
			free(line);
			line = hol;
		}
	}
	return (line);
}
