/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhyman <fhyman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:49:46 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/07/10 22:54:50 by fhyman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}					t_list;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *restrict dst, const char *restrict src, \
size_t dstsize);
size_t				ft_strlcat(char *restrict dst, const char *restrict src, \
size_t dstsize);
int					ft_atoi(char *str);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *restrict dst, const void *restrict src, \
int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle, \
size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strchr_int(const char *str, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
char				*ft_realloc(char *ptr, unsigned int size);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_strrncmp(char *s1, char *s2, size_t n);
void				add_new_line_to_arr(char ***arr, char *line);
void				print_arr(char **args);

#endif
