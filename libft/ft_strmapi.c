/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 08:08:45 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/06 12:47:03 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ss;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	ss = (char *)malloc(sizeof(char) * (i + 1));
	if (ss == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ss[i] = f(i, s[i]);
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
