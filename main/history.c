/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:08:38 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:08:39 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_history_file(char **envp)
{
	char	*home_dir;
	char	*hol;

	home_dir = ft_getenv("HOME=", envp);
	hol = ft_strjoin(home_dir, "/.minish_history");
	return (hol);
}

void	add_to_file_history(char *line, char **envp)
{
	int		fd;
	int		file_flags;
	mode_t	file_perms;
	char	*file;

	file_flags = O_APPEND | O_CREAT | O_WRONLY;
	file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	file = get_history_file(envp);
	fd = open(file, file_flags, file_perms);
	free(file);
	if (fd < 0)
		return ;
	if (line)
		ft_putendl_fd(line, fd);
	close(fd);
}

void	init_add_history(char **envp)
{
	int		fd;
	char	*line;
	char	*file;

	add_to_file_history(NULL, envp);
	file = get_history_file(envp);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	add_to_history(char *line, char **envp)
{
	add_to_file_history(line, envp);
	add_history(line);
}
