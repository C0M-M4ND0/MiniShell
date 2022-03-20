/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:08:01 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:08:03 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

DIR	*open_folder(char *name)
{
	DIR	*dir;

	if (quoted_wildcard(name))
		return (NULL);
	remove_quotes_1d(name);
	dir = opendir(".");
	if (dir == NULL)
		return (perror(ERR_DIR), NULL);
	return (dir);
}

char	*expand_wildcards(char *name)
{
	DIR				*dir;
	char			*hol;
	char			*hhol;
	struct dirent	*entry;

	hol = NULL;
	dir = open_folder(name);
	if (!dir)
		return (free(name), NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (!examin_entry_name(entry->d_name, name))
		{
			hhol = hol;
			hol = ft_strjoin((hol), entry->d_name);
			free(hhol);
			hhol = hol;
			hol = ft_strjoin((hol), " ");
			free(hhol);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), free(name), hol);
}

char	*join_expansion(char *line, char *line_hol, char *expanded, int last)
{
	line_hol = ft_strjoin(line, expanded);
	free(expanded);
	expanded = ft_strjoin(line_hol, &line[last]);
	free(line);
	free(line_hol);
	return (expanded);
}

char	*get_wildcards_expressions(char *line)
{
	int		i;
	int		f_i;
	int		last;
	char	*line_hol;
	char	*expanded;

	i = -1;
	f_i = 0;
	line_hol = NULL;
	while (line && line[++i])
	{
		i += check_quotes(&line[i]);
		if (is_token(line[i]))
			f_i = i + 1;
		if (line[i] == '*')
		{
			last = get_l_char_wildcard(&line[i]) + (i - f_i);
			expanded = expand_wildcards(ft_substr(line, f_i, last));
			if (!expanded)
				return (line);
			line[f_i] = '\0';
			line = join_expansion(line, line_hol, expanded, last + f_i);
		}
	}
	return (line);
}
