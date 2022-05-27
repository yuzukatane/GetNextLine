/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 11:07:38 by kyuzu             #+#    #+#             */
/*   Updated: 2022/05/27 11:07:41 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc((int)(s1_len + s2_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	i = 0;
	while (res[i] != '\0')
		i++;
	ft_strlcpy(&res[i], s2, s2_len + 1);
	free(s1);
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (i < dstsize - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i ++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

void	initbuff(size_t count, char *buff)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		buff[i] = '\0';
		i++;
	}
}
