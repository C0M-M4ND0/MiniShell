/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:14 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:17 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_here_doc_input(char *cmd, int stdin_dup)
{
	int	i;
	int	hol;

	i = 0;
	hol = -1;
	while (cmd[i])
	{
		i += check_quotes(&cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
		{
			if (hol != -1)
				to_space(cmd, hol, 2);
			hol = i;
			here_doc(f_io_names(&cmd[i + 2], 1), stdin_dup);
		}
		i++;
	}
}
