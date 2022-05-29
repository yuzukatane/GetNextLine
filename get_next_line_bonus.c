/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:52:37 by kyuzu             #+#    #+#             */
/*   Updated: 2022/05/29 18:02:55 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*save[256] = {NULL};
	char		*buff;
	t_line		line;
	int			flag;

	if (prepare_and_check(fd, &save[fd], &buff, &line) == FAIL)
		return (NULL);
	while (1)
	{
		flag = read_fd(fd, buff, &line);
		if (flag == FAIL || flag == SUCCESS)
			return (free_memory(save[fd], buff, line.str, flag));
		flag = find_linebreak(&save[fd], &line);
		if (flag == FAIL || flag == SUCCESS)
			return (free_memory(save[fd], buff, line.str, flag));
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
// 	int		fd0;
// 	int		fd1;
// 	int		fd2;
// 	char	*s0;
// 	char	*s1;
// 	char	*s2;

// 	if (BUFFER_SIZE <= 0)
// 		return (0);
// 	if (argc == 1)
// 	{
// 		fd0 = 1;
// 		while (1)
// 		{
// 			s0 = get_next_line(fd0);
// 			if (s0 == NULL)
// 				break ;
// 			printf("%s", s0);
// 			free(s0);
// 		}
// 	}
// 	else
// 	{
// 		fd1 = open(argv[1], O_RDONLY);
// 		fd2 = open(argv[2], O_RDONLY);
// 		while (1)
// 		{
// 			s1 = get_next_line(fd1);
// 			if (s1 == NULL)
// 				break ;
// 			s2 = get_next_line(fd2);
// 			if (s2 == NULL)
// 				break ;
// 			printf("%s", s1);
// 			printf("%s", s2);
// 			free(s1);
// 			free(s2);
// 		}
// 		printf("\n");
// 		close(fd1);
// 		close(fd2);
// 	}
// 	return (0);
// }