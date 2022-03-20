/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:04:34 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:36:38 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*hol;

	hol = *lst;
	if (lst != NULL)
	{
		while (*lst != NULL)
		{
			hol = (*lst)->next;
			if (del)
				del((*lst)->content);
			free(*lst);
			*lst = hol;
		}
	}
}
