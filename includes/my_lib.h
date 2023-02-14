#ifndef MY_LIB_H
# define MY_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

typedef struct s_string
{
    // Returns an int from a passed string.
    int 	(*_atoi)(const char *str);
    // Returns the length of a string.
    int 	(*_length)(const char *str);
    // Return a pointer to where it found 'char c' in string.
    char* 	(*_rear_search)(const char *str, char to_find);
    // Finds needle in haystack and no more than len characters are searched. 
    // If found, it returns a pointer to where it started. 
	char*	(*_strnstr)(const char *str, const char *to_find, unsigned int);
    // Return a new alloc'd string with a 'len' length and starting in s[start].
    char* 	(*_substr)(const char *str, unsigned int start, unsigned int len);
    // Returns a passed letter in lowercase.
    char 	(*_to_lower)(char c);
    // Returns a passed letter in uppercase.
    char 	(*_to_upper)(char c);
    // Compare if s2 == s1 no more than n characters. 
    // Return the difference if different, 0 if the same.
    int	    (*_compare_n)(const char* s1, const char* s2, unsigned int n);
    // Compares if s2 == s1. 
    // Return the difference if different. 0 if the same.
    int	    (*_compare)(const char* s1, const char* s2);
    // Returns a new alloc'd string appending s2 to s1.
    char*	(*_append)(char** s1, const char* s2);
    // Returns a pointer to where it found 'char c' in string.
    char*	(*_search)(const char *str, char c);
    // Copies (dstsize - 1) characters from src to dst. 
    // Return the amount of characters of the total string it tried to copy.
    int	    (*_copyl)(char *dst, const char *src, int dstsize);
    // Appends (dstsize - dst(len) - 1) characters from src to dst. 
    // Returns the amount of characters of the total string it tried to concatenate.
    int	    (*_concatenatel)(char *dst, const char *src, int dstsize);
    // Puts char in fd.
    void	(*_putchar_fd)(char c, int fd);
    // Puts string in fd.
    void	(*_putstring_fd)(char *s, int fd);
    // Puts number in fd.
    void	(*_putnumber_fd)(int n, int fd);
    // Returns an alloc'd string from a passed integer.
    char*   (*_itoa)(int n);
    // Erases the data in the n bytes of the memory starting at the location pointed to by s, by writing zeros (bytes containing '\0') to that area.
    void	(*_bzero)(void* str, unsigned int n);
    // Returns a malloc'd pointer initialized with 0's with sizeof(count * size) bytes. 
    void*   (*_calloc)(unsigned int count, unsigned int size);
    // Sets the array, one by one, no more than len characters to 'to_swap'.
    void*   (*_mem_set)(void *str, int to_swap, unsigned int len);
    // Returns a malloc'd string duplicated.
    char*   (*_duplicate)(const char *str);
    // Searches for 'c' in an array, no more than n characters. Return the address of n.
    void*	(*_mem_search)(const void *str, int c, unsigned int n);
    // Compares array1 with array2, no more than n characters.
    // Return the difference if different. 0 if the same.
    int	    (*_mem_compare)(const void *s1, const void *s2, unsigned int n);
    // Copies no more than n from array src to array dst, return a pointer to dst.
    void*   (*_mem_copy)(void *dst, const void *src, unsigned int n);
    // Copies from src to dst but uses a temporary array to do it.
    void*   (*_mem_move)(void *dst, const void *src, unsigned int len);
    // Puts string with new line in fd.
    void	(*_putstring_n_fd)(char *s, int fd);
    // Returns a splitted string.
    char**  (*_split)(char const *str, char c);
    char*	(*_mapi)(char const *s, char (*f)(unsigned int, char));
    // Returns a new alloc'd string having applied function f to every member of the string. 
    void	(*_iteri)(char *s, void (*f)(unsigned int, char*));
    char*	(*_trim)(char const *s1, char const *set);
    // Returns the number of _isspace delimited words. 
    int     (*_arg_count)(char *str);
    // Returns the number of characters in the string until the reach of char n. 0 if no string or char passed.
    int     (*_length_until_c)(char *str, char c);
    // Returns an allocated string that is copied until n characters.
    char*   (*_copy_until)(char *str, int n);
    // Returns the size of an array.
    int     (*_array_length)(char **array);
    // Checks if the word is the same as the string passed.
    int     (*_same_word)(char *w1, char *w2, int size);
    // Copies src to dst
    char*   (*_copy)(char *dst, char *src);
    // Joins s2 to s1. Allocates memory.
    char*	(*_join)(char const *s1, char const *s2);
}   t_string;

typedef struct s_check
{
    // Checks if 'c' is alpha. 2 for uppercase. 1 for lowercase. 0 for false.
    int	    (*_is_alpha)(int c);
    // Checks if c is ascii. 1 for true. 0 for false.
    int	    (*_is_ascii)(int c);
    // Checks if c is digit. 1 for true. 0 for false. 
    int	    (*_is_digit)(int c);
    // Checks if 32 >= c =< 126. 1 for true. 0 for false. 
    int	    (*_is_printable)(int c);
    // Checks if c is alpha or is digit. 1 for true. 0 for false.
    int	    (*_is_alnum)(int c);
    // Checks if c is space. 1 for true. 0 for false.
    int     (*_is_space)(int c);
    // Checks if path is a directory. 1 for true. 0 for false.
    int     (*_is_directory)(char *path);
    // Checks if char is meta_character. 1 for true. 0 for false.
    int     (*_is_meta_char)(char c);
}   t_check;

typedef struct s_list
{
    char            *token;
    int             type;
    struct s_list   *next;
} t_list;

typedef struct s_listfunc
{
    // Returns a pointer to a new node. 
    // Returns NULL if allocation fails.
    t_list*	(*_new_node)(void *content);

    // Returns the list size.
    int	    (*_size)(t_list *lst);

    // Returns a pointer to the last node of the list. 
    // Returns 0 if lst is NULL.
    t_list*	(*_last)(t_list *lst);

    // Adds a new node to the first position of the linked list and sets the head of the list to that new node.
    // The function returns if 'lst' is NULL.
    void    (*_add_front)(t_list **lst, t_list *new);

    // Adds a new node to the back of the linked list.
    // Returns if no list is passed.
    void	(*_add_back)(t_list **lst, void* content);

    // Applies a function to every member of the list.
    void	(*_iterator)(t_list *lst, void (*f)(void *));

    // Deletes the current node and sets lst pointer to next node. 
    // Frees removed node.
    void	(*_del_node)(t_list **lst);

    // Clears the whole list calling _del_node() to every member of the list.
    void	(*_clear_list)(t_list **lst);
    
    // Deletes the last node of the list.
    void    (*_del_last_node)(t_list **lst);
} t_listfunc;



// My lib function storer.
t_string    *string();
t_check     *check();
t_listfunc  *list();

char	_to_lower(char letter);
char	_to_upper(char letter);

char*   _append(char **s1, char const *s2);
char*   _strnstr(const char *str, const char *to_find, unsigned int len);
char*   _rear_search(const char *str, char c);
char*   _substr(const char *s, unsigned int start, unsigned int len);
char*	_search(const char *str, char c);
char*   _itoa(int n);
char*	_mapi(char const *s, char (*f)(unsigned int, char));
char*	_trim(char const *s1, char const *set);
char*   _duplicate(const char *str);
char*   _copy_until(char *str, int n);
char*   _copy(char *dst, char *src);
char*   _join(char const *s1, char const *s2);

char**  _split(char const *s, char c);

int     _arg_count(char *str);
int		_atoi(const char *str);
int 	_length(const char *str);
int	    _compare(const char* s1, const char* s2);
int	    _compare_n(const char *s1, const char *s2, unsigned int n);
int	    _copyl(char *dst, const char *src, int dstsize);
int	    _concatenatel(char *dst, const char *src, int dstsize);
int	    _is_alpha(int c);
int	    _is_ascii(int c);
int	    _is_digit(int c);
int	    _is_printable(int c);
int	    _is_alnum(int c);
int     _is_space(int c);
int     _is_meta_char(char c);
int	    _mem_compare(const void *s1, const void *s2, unsigned int n);
int     _length_until_c(char *str, char c);
int     _is_directory(char *path);
int	    _size(t_list *lst);
int     _array_length(char **array);
int     _same_word(char *w1, char *w2, int size);

void	_putchar_fd(char c, int fd);
void	_putstring_fd(char *s, int fd);
void	_putstring_n_fd(char *s, int fd);
void	_putnumber_fd(int n, int fd);
void	_bzero(void *str, unsigned int n);
void	_iteri(char *s, void (*f)(unsigned int, char*));
void    _add_front(t_list **lst, t_list *new);
void	_add_back(t_list **lst, void *content);
void	_iterator(t_list *lst, void (*f)(void *));
void	_del_node(t_list **lst);
void	_clear_list(t_list **lst);
void    _del_last_node(t_list **lst);

void*   _calloc(unsigned int count, unsigned int size);
void*   _mem_set(void *str, int to_swap, unsigned int len);
void*	_mem_search(const void *str, int c, unsigned int n);
void*   _mem_copy(void *dst, const void *src, unsigned int n);
void*   _mem_move(void *dst, const void *src, unsigned int len);

t_list	*_new_node(void *content);
t_list	*_last(t_list *lst);

#endif
