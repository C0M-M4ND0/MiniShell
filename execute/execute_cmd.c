/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:07:07 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:07:10 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_cmd(t_collect *var, char **envp)
{
	char	*full_cmd;
	int		i;

	if ((var->cmd[0] && !ft_strncmp(var->cmd[0], "..\0", 3)) || !var->cmd[0][0])
		return (NULL);
	if ((var->cmd[0][0] == '.' || var->cmd[0][0] == '/'))
		return (ft_strdup(var->cmd[0]));
	i = 0;
	var->slash_cmd = ft_strjoin("/", var->cmd[0]);
	var->paths = ft_split(ft_getenv("PATH=", envp), ':');
	while (var->paths && var->paths[i])
	{
		full_cmd = ft_strjoin(var->paths[i], var->slash_cmd);
		if (!access(full_cmd, F_OK))
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (NULL);
}

int	ignore_commande(char *line)
{
	int	i;
	int	f_i;

	i = 0;
	f_i = -1;
	while (line && line[i] == ' ')
		i++;
	if (line && line[i] == '(')
		f_i = i;
	i = ft_strlen(line) - 1;
	while (line && line[i] == ' ')
		i--;
	if (line && line[i] == ')' && f_i != -1)
		return (1);
	return (0);
}

void	check_exit_execution(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && cmd[i] == ' ')
		i++;
	if (!cmd || !cmd[i])
		exit(0);
}

void	check_cmd_format(t_collect *var, char *short_cmd)
{
	struct stat	buffer;

	if (!var->cmd[0] || !var->cmd[0][0])
		exit_error(var, short_cmd, CMD_ERROR, 127);
	if (!ft_strncmp(var->cmd[0], ".\0", 2))
		exit_error(var, short_cmd, ERR_USAGE, 2);
	if (stat(var->cmd[0], &buffer))
		exit_error(var, short_cmd, NULL, 126);
	else if (buffer.st_mode & S_IFDIR)
		exit_error(var, short_cmd, ERR_ISDIR, 126);
	else if ((buffer.st_mode & S_IXUSR) == 0 || (buffer.st_mode & S_IRUSR) == 0)
		exit_error(var, short_cmd, ERR_PERM, 126);
}

void	execute_cmd(char *cmd, char **envp)
{
	t_collect	var;
	char		*hol;

	var = (t_collect){};
	check_exit_execution(cmd);
	var.cmd = ft_split(cmd, ' ');
	remove_quotes_2d(var.cmd);
	hol = var.cmd[0];
	var.cmd[0] = check_cmd(&var, envp);
	check_cmd_format(&var, hol);
	execve(var.cmd[0], var.cmd, envp);
	exit_error(&var, hol, NULL, 127);
}
