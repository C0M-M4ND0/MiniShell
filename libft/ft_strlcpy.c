/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:03:05 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/08 12:31:10 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	j;
	int		i;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	if (dstsize != 0)
	{
		while ((src[j] != '\0') && (j < (dstsize - 1)))
		{
			dest[j] = src[j];
			j++;
		}
		dest[j] = '\0';
	}
	return (i);
}
