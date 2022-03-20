/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:07:43 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/06 12:21:01 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nel;

	nel = (t_list *)malloc(sizeof (t_list));
	if (nel == NULL)
		return (nel);
	nel->content = content;
	nel->next = NULL;
	return (nel);
}
