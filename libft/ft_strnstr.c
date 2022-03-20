/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:01:36 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/10 18:11:40 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{	
	size_t	i;
	size_t	r;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		r = 0;
		while ((i + r) < len && haystack[i + r] && haystack[i + r] == needle[r])
		{
			if (needle[r + 1] == '\0')
			{
				return ((char *)((haystack + i)));
			}
			r++;
		}
		i++;
	}
	return (NULL);
}
