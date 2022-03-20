/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:37:56 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/08 09:07:29 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc((size_t)len);
	if (s == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (++i >= 0 && s1 && s1[i])
		s[i] = s1[i];
	while (s2 && s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}
