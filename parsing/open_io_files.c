/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:10:11 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:10:13 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_input_file(char *infile, int stdin_no)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(infile, STDERR_FILENO);
		perror (" \b");
		free(infile);
		return (-2);
	}
	free(infile);
	dup2(stdin_no, STDIN_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (1);
}

int	open_output_file(char *outfile, int mode)
{
	int		fd_out;
	int		outfile_flags;
	mode_t	outfile_perms;

	if (mode == APPEND_MODE)
		outfile_flags = O_APPEND | O_CREAT | O_WRONLY;
	else
		outfile_flags = O_TRUNC | O_CREAT | O_WRONLY;
	outfile_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd_out = open(outfile, outfile_flags, outfile_perms);
	if (fd_out < 0)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(outfile, STDERR_FILENO);
		perror (" \b");
		free(outfile);
		return (-2);
	}
	free(outfile);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (1);
}
