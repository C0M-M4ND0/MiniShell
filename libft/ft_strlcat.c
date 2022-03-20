/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:10:06 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/08 12:31:58 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char	*dest, const char *src, size_t dstsize)
{
	size_t	r;
	size_t	i;
	size_t	j;
	size_t	t;

	r = 0;
	j = 0;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
		j++;
	if (dstsize != 0 && i < dstsize)
	{
		t = i;
		while ((i < (t + j)) && (i < (dstsize - 1)))
		{
			dest[i] = src[r];
			i++;
			r++;
		}
		dest[i] = '\0';
		return (t + j);
	}
	return (j + dstsize);
}
