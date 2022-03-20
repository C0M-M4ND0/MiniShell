/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:06:13 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:06:25 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str_to_lower(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}

int	check_num_arg(char c, char *error_msg)
{
	if (ft_isdigit(c))
	{
		ft_putendl_fd(error_msg, STDERR_FILENO);
		return (g_vars.exit_code = 1, 1);
	}
	return (0);
}
