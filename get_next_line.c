/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:52:37 by kyuzu             #+#    #+#             */
/*   Updated: 2022/05/27 10:59:02 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*buff;
	t_line		line;
	int			flag;

	if (prepare_and_check(fd, &save, &buff, &line) == FAIL)
		return (NULL);
	while (1)
	{
		flag = read_fd(fd, buff, &line);
		if (flag == FAIL || flag == SUCCESS)
			return (free_memory(save, buff, line.str, flag));
		flag = find_linebreak(&save, &line);
		if (flag == FAIL || flag == SUCCESS)
			return (free_memory(save, buff, line.str, flag));
	}
	return (NULL);
}

int	prepare_and_check(int fd, char **save, char **buff, t_line *line)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (FAIL);
	*buff = NULL;
	line->str = NULL;
	*buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buff == NULL)
		return (FAIL);
	if (*save != NULL)
	{
		line->str = *save;
		*save = NULL;
	}
	line->index = 0;
	return (SUCCESS);
}

int	read_fd(int fd, char *buff, t_line *line)
{
	int	readn;

	initbuff(BUFFER_SIZE + 1, buff);
	readn = read(fd, buff, BUFFER_SIZE);
	if (readn == -1)
		return (FAIL);
	else if (readn == 0
		&& (line->str == NULL || line->str[line->index] == '\0'))
		return (line->str != NULL);
	else
	{
		if (line->str == NULL)
			line->str = ft_strdup(buff);
		else
			line->str = ft_strjoin(line->str, buff);
		if (line->str == NULL)
			return (FAIL);
	}
	return (PASS);
}

int	find_linebreak(char **save, t_line *line)
{
	while (line->str[line->index] != '\0')
	{
		if (line->str[line->index] == '\n')
		{
			if (line->str[line->index + 1] != '\0')
			{
				*save = ft_strdup(&line->str[line->index + 1]);
				if (*save == NULL)
					return (FAIL);
				line->str[line->index + 1] = '\0';
			}
			return (SUCCESS);
		}
		line->index++;
	}
	return (PASS);
}

char	*free_memory(char *save, char *buff, char *str, int flag)
{
	if (flag == SUCCESS)
	{
		if (buff)
			free(buff);
		return (str);
	}
	else
	{
		if (save)
			free(save);
		if (buff)
			free(buff);
		if (str)
			free(str);
		return (NULL);
	}
}

// #include <stdio.h>

// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	int		i;
// 	char	*s;

// 	if (BUFFER_SIZE <= 0)
// 		return (0);
// 	if (argc == 1)
// 	{
// 		fd = 1;
// 		while (1)
// 		{
// 			s = get_next_line(fd);
// 			if (s == NULL)
// 				break ;
// 			printf("%s", s);
// 			free(s);
// 		}
// 	}
// 	else
// 	{
// 		i = 1;
// 		while (i < argc)
// 		{
// 			fd = open(argv[i], O_RDONLY);
// 			while (1)
// 			{
// 				s = get_next_line(fd);
// 				if (s == NULL)
// 					break ;
// 				printf("%s", s);
// 				free(s);
// 			}
// 			printf("\n");
// 			close(fd);
// 			i++;
// 		}
// 	}
// 	return (0);
// }
