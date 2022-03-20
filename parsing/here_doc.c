/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:34 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:36 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	creat_here_doc_file(t_list *strs_holder)
{
	int		fd_in;
	int		infile_flags;
	mode_t	infile_perms;

	infile_flags = O_TRUNC | O_CREAT | O_WRONLY;
	infile_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd_in = open(".heredoc.tmp", infile_flags, infile_perms);
	if (fd_in < 0)
		return (ft_putstr_fd("here_doc", STDERR_FILENO), perror (" \b"), 0);
	while (strs_holder)
	{
		ft_putstr_fd(strs_holder->content, fd_in);
		ft_putstr_fd("\n", fd_in);
		free(strs_holder->content);
		strs_holder = strs_holder->next;
	}
	close (fd_in);
	return (1);
}

char	*here_doc(char *limiter, int stdin_no)
{
	t_list	*strs_holder;
	char	*line;

	strs_holder = NULL;
	dup2(stdin_no, STDIN_FILENO);
	unlink(".heredoc.tmp");
	while (1)
	{
		g_vars.sig_indice = -1;
		line = readline_config("heredoc> ");
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(limiter))
				&& line[ft_strlen(limiter)] == '\0'))
			break ;
		ft_lstadd_back(&strs_holder, ft_lstnew(line));
	}
	if (!creat_here_doc_file(strs_holder))
		return (ft_lstclear(&strs_holder, NULL), NULL);
	ft_lstclear(&strs_holder, NULL);
	return (ft_strdup(".heredoc.tmp"));
}
