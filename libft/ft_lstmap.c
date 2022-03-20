/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 08:41:10 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/07 18:36:32 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*hilst;
	t_list	*pilst;

	hilst = NULL;
	while (lst != NULL)
	{
		pilst = ft_lstnew(f(lst->content));
		if (pilst == NULL)
		{
			ft_lstclear(&hilst, del);
			return (NULL);
		}
		ft_lstadd_back(&hilst, pilst);
		lst = lst->next;
	}
	return (hilst);
}
