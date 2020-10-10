/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 12:18:31 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/10 10:24:33 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int				get_next_line(int fd, char **line);
size_t			ft_strlen2(char *str);
char			*ft_strchr2(char *s, int c);
char			*ft_strcpy2(char *dest, char *src);
char			*ft_strdup2(char *s);
char			*ft_strjoin_gnl(char *s1, char *s2);

#endif
