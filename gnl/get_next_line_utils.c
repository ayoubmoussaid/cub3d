/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:22:22 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/20 10:21:04 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (0);
	return (char *)s;
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (src[i] != '\0')
		i++;
	str = (char*)malloc(i + 1);
	if (str)
	{
		i = 0;
		while (src[i] != '\0')
		{
			str[i] = src[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	n;
	unsigned int	m;

	if (!s1 && !s2)
		return (NULL);
	n = ft_strlen((char*)s1);
	m = ft_strlen((char*)s2);
	newstr = (char*)malloc(n + m + 1);
	if (newstr == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
		newstr[i] = s1[i];
	while (i - n < m)
	{
		newstr[i] = s2[i - n];
		i++;
	}
	newstr[i] = '\0';
	free(s1);
	free(s2);
	return (newstr);
}

char	*ft_substr1(char *s, unsigned int start,
	size_t len)
{
	char			*sub;
	unsigned long	i;
	unsigned int	max;

	if (s == NULL)
		return (NULL);
	i = 0;
	max = ft_strlen(s);
	sub = (char*)malloc(len + 2);
	if (sub == NULL)
		return (NULL);
	while (start < max && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	free(s);
	return (sub);
}
