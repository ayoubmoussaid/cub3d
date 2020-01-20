/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:02:49 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/20 10:21:53 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_checker(char *str, int nm)
{
	unsigned int n;

	n = 0;
	while ((str[n]) && (str[n] != '\n'))
		n++;
	if (nm == 1)
		return (ft_substr1(str, 0, n));
	return (ft_substr1(str, n + 1, ft_strlen(str) - n - 1));
}

int		does_it_end(char *str)
{
	unsigned int i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '\0')
		return (0);
	if (ft_strchr(str, '\n') != 0)
		return (1);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\0')
			return (2);
		i++;
	}
	return (0);
}

char	*read_buffer(int fd, char *buffer)
{
	size_t	x;
	char	*str;

	str = (char*)malloc(BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	x = read(fd, str, BUFFER_SIZE);
	str[x] = '\0';
	free(buffer);
	if (x == 0)
	{
		free(str);
		return (NULL);
	}
	buffer = ft_strjoin1(ft_strdup(""), str);
	return (buffer);
}

char	*verify_line(char **line, char *buffer, int x)
{
	if (x == 0)
	{
		*line = ft_strjoin1(*line, buffer);
		buffer = ft_strdup("\0");
	}
	if (x == 1)
	{
		*line = ft_strjoin1(*line, str_checker(ft_strdup(buffer), 1));
		buffer = str_checker(buffer, 0);
	}
	return (buffer);
}

int		get_next_line(int fd, char **line)
{
	static char *buffer;

	if (fd < 0 || !line || read(fd, buffer, 0) == -1)
		return (-1);
	*line = ft_strdup("");
	while (1)
	{
		if ((buffer != NULL) && *buffer != '\0' &&
			((ft_strchr(buffer, '\n') == 0) || does_it_end(buffer) == 0))
			buffer = verify_line(line, buffer, 0);
		else if ((buffer != NULL) && (does_it_end(buffer) == 1))
			break ;
		if ((buffer = read_buffer(fd, buffer)) == NULL)
			return (0);
		if (does_it_end(buffer) == 1)
			break ;
		if (does_it_end(buffer) == 2)
		{
			*line = ft_strjoin1(*line, buffer);
			return (0);
		}
		buffer = verify_line(line, buffer, 0);
	}
	buffer = verify_line(line, buffer, 1);
	return (1);
}
