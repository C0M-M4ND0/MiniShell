/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:37:04 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/07 09:41:19 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char	*s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	us1;
	unsigned char	us2;

	if (n == 0 || !s1 || !s2)
		return (0);
	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i] && i < n - 1)
		i++;
	us1 = s1[i];
	us2 = s2[i];
	return ((us1 - us2));
}
