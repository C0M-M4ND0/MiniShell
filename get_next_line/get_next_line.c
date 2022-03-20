/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 09:09:20 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/21 11:13:37 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_rline(char *hol, int i)
{
	int		j;
	char	*rline;

	if (hol == NULL)
		return (NULL);
	j = -1;
	if (i < 0)
		i = ft_strlen2(hol) - 1;
	rline = (char *)malloc((size_t)(i + 2));
	if (rline == NULL)
		return (NULL);
	while (hol[++j] && hol[j] != '\n')
		rline[j] = hol[j];
	rline[j] = '\0';
	return (rline);
}

char	*ft_nline(char *hol)
{
	int		j;
	char	*nline;
	int		i;

	j = 0;
	i = ft_strchr2(hol);
	if (i == (ft_strlen2(hol) - 1))
	{
		free(hol);
		return (NULL);
	}
	if (hol == NULL || (ft_strchr2(hol)) < 0)
		return (NULL);
	nline = (char *)malloc((size_t)(ft_strlen2(hol) - i));
	if (nline == NULL)
		return (NULL);
	while (hol[++i])
		nline[j++] = hol[i];
	nline[j] = '\0';
	free(hol);
	hol = NULL;
	return (nline);
}

char	*get_next_line(int fd)
{
	static char	*hol;
	char		*buf;
	int			rt;

	hol = ft_nline(hol);
	if ((ft_strchr2(hol)) > 0)
		return (ft_rline(hol, ft_strchr2(hol)));
	buf = (char *)malloc((size_t)(BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (ft_strchr2(hol) < 0)
	{
		rt = read(fd, buf, BUFFER_SIZE);
		if (rt <= 0)
			break ;
		hol = ft_strjoin2(hol, buf, rt);
	}
	free(buf);
	if (rt < 0)
		return (NULL);
	if (rt == 0 && (ft_strchr2(hol)) < 0)
		return (hol);
	return (ft_rline(hol, ft_strchr2(hol)));
}
