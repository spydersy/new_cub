/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 20:18:43 by abelarif          #+#    #+#             */
/*   Updated: 2021/01/11 18:00:41 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>

# include <string.h>

# include <stdlib.h>

# include "../libft_utils/libft.h"

#define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
int		ft_checkvalue(int read_value, char **line, char *rest, char *buf);
char	*free_all(char *buf, char **rest);
size_t	ft_strlen(const char *s);
int		check_nl(const char *rest);
char	*strjoin(char **rest, char *buf);
char	*r_r(char *rest, int index_nl);
char	*r_l(char *rest, int index_nl);
char	*ft_strdup(const char *s1);

#endif
