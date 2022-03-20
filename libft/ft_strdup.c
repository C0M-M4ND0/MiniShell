/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 09:28:48 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/11 15:52:11 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*dup;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	len = i + 1;
	i = -1;
	dup = (char *)malloc(len * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (s1[++i])
		dup[i] = s1[i];
	dup[i] = '\0';
	return (dup);
}
