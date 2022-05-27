/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:53:02 by kyuzu             #+#    #+#             */
/*   Updated: 2022/05/27 11:38:17 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_line {
	char	*str;
	int		index;
}	t_line;

enum e_flag {
	FAIL = 0,
	SUCCESS = 1,
	PASS = 2
};

char	*get_next_line(int fd);
void	initbuff(size_t count, char *buff);
int		prepare_and_check(int fd, char **save, char **buff, t_line *line);
int		read_fd(int fd, char *buff, t_line *line);
int		find_linebreak(char **save, t_line *line);
char	*free_memory(char *save, char *buff, char *str, int flag);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

#endif
