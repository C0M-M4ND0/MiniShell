/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:21:58 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/10 18:54:16 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	j;

	j = 0;
	while (s[j])
		j++;
	if (c == '\0')
		return ((char *)&s[j]);
	while (--j >= 0)
	{
		if (s[j] == (unsigned char)c)
			return ((char *)&s[j]);
	}
	return (NULL);
}
