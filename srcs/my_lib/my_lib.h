/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:54:58 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 17:35:30 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_LIB_H
# define MY_LIB_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_string
{
	int		(*_atoi)(const char *str);
	int		(*_length)(const char *str);
	char	*(*_rear_search)(const char *str, char to_find);
	char	*(*_strnstr)(const char *str, const char *to_find, unsigned int);
	char	*(*_substr)(const char *str, unsigned int start, unsigned int len);
	char	(*_to_lower)(char c);
	char	(*_to_upper)(char c);
	int		(*_compare_n)(const char *s1, const char *s2, unsigned int n);
	int		(*_compare)(const char *s1, const char *s2);
	char	*(*_append)(char **s1, const char *s2);
	char	*(*_search)(const char *str, char c);
	int		(*_copyl)(char *dst, const char *src, int dstsize);
	int		(*_concatenatel)(char *dst, const char *src, int dstsize);
	void	(*_putchar_fd)(char c, int fd);
	void	(*_putstring_fd)(char *s, int fd);
	void	(*_putnumber_fd)(int n, int fd);
	char	*(*_itoa)(int n);
	void	(*_bzero)(void *str, unsigned int n);
	void	*(*_calloc)(unsigned int count, unsigned int size);
	void	*(*_mem_set)(void *str, int to_swap, unsigned int len);
	char	*(*_duplicate)(const char *str);
	void	*(*_mem_search)(const void *str, int c, unsigned int n);
	int		(*_mem_compare)(const void *s1, const void *s2, unsigned int n);
	void	*(*_mem_copy)(void *dst, const void *src, unsigned int n);
	void	*(*_mem_move)(void *dst, const void *src, unsigned int len);
	void	(*_putstring_n_fd)(char *s, int fd);
	char	**(*_split)(char const *str, char c);
	char	*(*_mapi)(char const *s, char (*f)(unsigned int, char));
	void	(*_iteri)(char *s, void (*f)(unsigned int, char*));
	char	*(*_trim)(char const *s1, char const *set);
	int		(*_arg_count)(char *str);
	int		(*_length_until_c)(char *str, char c);
	char	*(*_copy_until)(char *str, int n);
	int		(*_array_length)(char **array);
	int		(*_same_word)(char *w1, char *w2, int size);
	char	*(*_copy)(char *dst, char *src);
	char	*(*_join)(char const *s1, char const *s2);
}	t_string;

typedef struct s_check
{
	int		(*_is_alpha)(int c);
	int		(*_is_ascii)(int c);
	int		(*_is_digit)(int c);
	int		(*_is_printable)(int c);
	int		(*_is_alnum)(int c);
	int		(*_is_space)(int c);
	int		(*_is_directory)(char *path);
	int		(*_is_meta_char)(char c);
}	t_check;

typedef struct s_list
{
	char			*token;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_listfunc
{
	t_list	*(*_new_node)(void *content);
	int		(*_size)(t_list *lst);
	t_list	*(*_last)(t_list *lst);
	void	(*_add_front)(t_list **lst, t_list *new);
	void	(*_add_back)(t_list **lst, void *content);
	void	(*_iterator)(t_list *lst, void (*f)(void *));
	void	(*_del_node)(t_list **lst);
	void	(*_clear_list)(t_list **lst);
	void	(*_del_last_node)(t_list **lst);
}	t_listfunc;

t_string	*string(void);
t_check		*check(void);
t_listfunc	*list(void);

char		_to_lower(char letter);
char		_to_upper(char letter);

char		*_append(char **s1, char const *s2);
char		*_strnstr(const char *str, const char *to_find, unsigned int len);
char		*_rear_search(const char *str, char c);
char		*_substr(const char *s, unsigned int start, unsigned int len);
char		*_search(const char *str, char c);
char		*_itoa(int n);
char		*_mapi(char const *s, char (*f)(unsigned int, char));
char		*_trim(char const *s1, char const *set);
char		*_duplicate(const char *str);
char		*_copy_until(char *str, int n);
char		*_copy(char *dst, char *src);
char		*_join(char const *s1, char const *s2);

char		**_split(char const *s, char c);

int			_arg_count(char *str);
int			_atoi(const char *str);
int			_length(const char *str);
int			_compare(const char *s1, const char *s2);
int			_compare_n(const char *s1, const char *s2, unsigned int n);
int			_copyl(char *dst, const char *src, int dstsize);
int			_concatenatel(char *dst, const char *src, int dstsize);
int			_is_alpha(int c);
int			_is_ascii(int c);
int			_is_digit(int c);
int			_is_printable(int c);
int			_is_alnum(int c);
int			_is_space(int c);
int			_is_meta_char(char c);
int			_mem_compare(const void *s1, const void *s2, unsigned int n);
int			_length_until_c(char *str, char c);
int			_is_directory(char *path);
int			_size(t_list *lst);
int			_array_length(char **array);
int			_same_word(char *w1, char *w2, int size);

void		_putchar_fd(char c, int fd);
void		_putstring_fd(char *s, int fd);
void		_putstring_n_fd(char *s, int fd);
void		_putnumber_fd(int n, int fd);
void		_bzero(void *str, unsigned int n);
void		_iteri(char *s, void (*f)(unsigned int, char*));
void		_add_front(t_list **lst, t_list *new);
void		_add_back(t_list **lst, void *content);
void		_iterator(t_list *lst, void (*f)(void *));
void		_del_node(t_list **lst);
void		_clear_list(t_list **lst);
void		_del_last_node(t_list **lst);

void		*_calloc(unsigned int count, unsigned int size);
void		*_mem_set(void *str, int to_swap, unsigned int len);
void		*_mem_search(const void *str, int c, unsigned int n);
void		*_mem_copy(void *dst, const void *src, unsigned int n);
void		*_mem_move(void *dst, const void *src, unsigned int len);

t_list		*_new_node(void *content);
t_list		*_last(t_list *lst);

#endif
