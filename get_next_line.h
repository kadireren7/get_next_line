/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaltint@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 19:06:09 by kaaltint          #+#    #+#             */
/*   Updated: 2026/11/19 19:34:59 by kaaltint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		gnl_has_newline(char *str);
size_t	gnl_strlen(char *str);
char	*gnl_join(char *str1, char *str2);
char	*gnl_extract_line(char *stash);
char	*gnl_clean_stash(char *stash);

#endif
