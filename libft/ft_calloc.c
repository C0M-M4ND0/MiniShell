/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:23:12 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/06 11:05:22 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*p;
	int		m;

	m = size * count;
	ptr = malloc(m);
	if (ptr == NULL)
		return (NULL);
	p = ptr;
	while (m-- > 0)
		*p++ = 0;
	return (ptr);
}
