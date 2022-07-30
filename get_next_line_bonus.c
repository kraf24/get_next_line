/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchuk <gpinchuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 14:23:14 by gpinchuk          #+#    #+#             */
/*   Updated: 2022/05/19 15:29:21 by gpinchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *string, char *buff)
{
	size_t	n1;
	size_t	len;
	char	*str;

	if (!string)
	{
		string = (char *)malloc(sizeof(char));
		string[0] = '\0';
	}
	if (!string || !buff)
		return (NULL);
	n1 = ft_strlen(string);
	len = ft_strlen(buff) + (n1) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (str == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(str, (char *)string, ft_strlen(string) + 1);
	ft_strlcpy(&str[n1], (char *)buff, ft_strlen(buff) + 1);
	free(string);
	return (str);
}

char	*ft_read_from_file(int fd, char *left)
{
	char	*buff;
	int		size;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	size = 1;
	while (!(ft_strchr(left, '\n')) && size)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[size] = '\0';
		left = ft_strjoin(left, buff);
	}
	free(buff);
	return (left);
}

char	*get_next_line(int fd)
{
	char		*string;
	static char	*left[1024];

	left[fd] = ft_read_from_file(fd, left[fd]);
	if (!left[fd] || BUFFER_SIZE < 0)
		return (NULL);
	string = ft_new_string(left[fd]);
	left[fd] = ft_get_new_string(left[fd]);
	return (string);
}
