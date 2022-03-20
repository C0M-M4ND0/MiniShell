/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:37:13 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/11 18:31:13 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	void	ft_fill(char *snum, long n, int i)
{
	int	j;

	j = 0;
	snum[i--] = '\0';
	if (n < 0)
	{
		j = 1;
		n = -n;
	}
	while (i > j)
	{
		snum[i--] = "0123456789"[n % 10];
		n /= 10;
	}
	snum[i] = "0123456789"[n];
}

static	int	ft_count(long m)
{
	int	i;

	i = 0;
	if (m < 0)
	{
		m = -m;
		i++;
	}
	while (m > 9)
	{
		m /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*snum;
	long	m;

	i = 1;
	m = (long)n;
	i = ft_count(m);
	snum = (char *)malloc(sizeof(char) * (i + 2));
	if (snum == NULL)
		return (NULL);
	if (n < 0)
		snum[0] = '-';
	ft_fill(snum, m, i + 1);
	return (snum);
}
