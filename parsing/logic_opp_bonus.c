/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_opp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:47 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:48 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_logic(char *cmds, char **envp)
{
	char	*l_cmd;
	int		logic_opp;

	if (check_priorities(cmds))
		return (parse_logic(cmds, envp));
	logic_opp = 0;
	l_cmd = get_last_cmd(cmds, &logic_opp);
	if (!l_cmd)
		parse_input(cmds, envp);
	else
		parse_logic(cmds, envp);
	if (logic_opp == 1 && g_vars.exit_code)
	{
		if (check_priorities(l_cmd))
			return (parse_logic(l_cmd, envp));
		parse_input(l_cmd, envp);
	}
	else if (logic_opp == -1 && !g_vars.exit_code)
	{
		if (check_priorities(l_cmd))
			return (parse_logic(l_cmd, envp));
		parse_input(l_cmd, envp);
	}
}
