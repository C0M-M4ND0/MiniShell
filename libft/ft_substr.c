/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:52:29 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/10 20:47:09 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*ss;
	char	*bb;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	ss = (char *)&s[start];
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	sub = (char *)malloc((size_t)(len + 1));
	if (sub == NULL)
		return (NULL);
	bb = sub;
	while (len-- > 0)
		*bb++ = *ss++;
	*bb = '\0';
	return (sub);
}
