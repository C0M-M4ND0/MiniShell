/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:07:27 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:07:29 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_builtin(int r_builtint)
{
	if (r_builtint < 0)
		exit(1);
	exit(0);
}

int	fork_here_doc(char *cmd, int stdin_dup)
{
	int	status;
	int	pid_child;

	pid_child = fork();
	if (pid_child == -1)
		return (perror("minish: fork"), 1);
	else if (!pid_child)
	{
		get_here_doc_input(cmd, stdin_dup);
		exit(0);
	}
	waitpid(pid_child, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		g_vars.exit_code = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

void	fork_child_1(char *cmd, int stdin_dup, int *fd, char **envp)
{
	int	r_io;

	r_io = 0;
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	while (r_io != -1)
	{
		r_io = get_io_files(cmd, stdin_dup);
		if (r_io == -2)
			exit(1);
	}
	execute_cmd(cmd, envp);
}

void	fork_child_2(char *cmd, int stdin_dup, char **envp)
{
	int	r_io;

	r_io = 0;
	get_here_doc_input(cmd, stdin_dup);
	while (r_io != -1)
	{
		r_io = get_io_files(cmd, stdin_dup);
		if (r_io == -2)
			exit(1);
	}
	execute_cmd(cmd, envp);
}

void	get_exit_code(int pid, int *status)
{
	if (pid == -1)
		return (perror("minish: fork"));
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		g_vars.exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		g_vars.exit_code = WTERMSIG(*status) + 128;
		if (g_vars.exit_code == 130)
			printf("\n");
		else if (g_vars.exit_code == 131)
			printf("Quit: 3\n");
	}
	close(STDIN_FILENO);
	while (waitpid(-1, status, 0) > 0)
		;
	if (WIFSIGNALED(*status) && g_vars.exit_code < 128)
	{
		if (WTERMSIG(*status) == 2)
			printf("\n");
		else if (WTERMSIG(*status) == 3)
			printf("Quit: 3\n");
	}
}
