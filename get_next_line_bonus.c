/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-aou <bben-aou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:59:12 by bben-aou          #+#    #+#             */
/*   Updated: 2021/12/19 10:33:21 by bben-aou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_checkline(char *svar)
{
	int		i;
	char	*ar;

	i = 0;
	if (!svar[i])
		return (NULL);
	while (svar[i] && svar[i] != '\n')
		i++;
	ar = (char *)malloc(sizeof(char) * (i + 2));
	if (!ar)
		return (NULL);
	i = 0;
	while (svar[i] && svar[i] != '\n')
	{
		ar[i] = svar[i];
		i++;
	}
	if (svar[i] == '\n')
	{
		ar[i] = svar[i];
		i++;
	}
	ar[i] = '\0';
	return (ar);
}

char	*ft_nextline(char *svar)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (svar[i] && svar[i] != '\n')
		i++;
	if (!svar[i])
	{
		free(svar);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen(svar) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (svar[i])
		temp[j++] = svar[i++];
	temp[j] = '\0';
	free(svar);
	return (temp);
}

char	*ft_fill_line(int fd, char *svar)
{
	char	*buff;
	int		b;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	b = 1;
	while (!ft_strchr(svar, '\n') && b != 0)
	{
		b = read(fd, buff, BUFFER_SIZE);
		if (b == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[b] = '\0';
		svar = ft_strjoin(svar, buff);
	}
	free(buff);
	return (svar);
}

char	*get_next_line(int fd)
{
	static char	*svar[10240];
	char		*checkedline;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (0);
	svar[fd] = ft_fill_line(fd, svar[fd]);
	if (!svar[fd])
		return (NULL);
	checkedline = ft_checkline(svar[fd]);
	svar[fd] = ft_nextline(svar[fd]);
	return (checkedline);
}
