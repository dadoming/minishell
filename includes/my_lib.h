#ifndef MY_LIB_H
# define MY_LIB_H



typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;


typedef struct s_string
{
    int 	(*_atoi)(const char *str);
    int 	(*_length)(const char *str);
    char* 	(*_rear_search)(const char *str, char to_find);
	char*	(*_strnstr)(const char *str, const char *to_find, unsigned int);
    char* 	(*_substr)(const char *str, unsigned int start, unsigned int len);
    char 	(*_to_lower)(char c);
    char 	(*_to_upper)(char c);
    int	    (*_compare_n)(const char* s1, const char* s2, unsigned int n);
    int	    (*_compare)(const char* s1, const char* s2);
    char	(*_append)(const char* s1, const char* s2);
    char*	(*_search)(const char *str, char c);
    int	    (*_copyl)(char *dst, const char *src, int dstsize);
    int	    (*_concatenatel)(char *dst, const char *src, int dstsize);
    void	(*_putchar_fd)(char c, int fd);
    void	(*_putstring_fd)(char *s, int fd);
    void	(*_putnumber_fd)(int n, int fd);
    int	    (*_is_alpha)(int c);
    int	    (*_is_ascii)(int c);
    int	    (*_is_digit)(int c);
    int	    (*_is_printable)(int c);
    int	    (*_is_alnum)(int c);
    char*   (*_itoa)(int n);
    void	(*_bzero)(void* str, unsigned int n);
    void*   (*_calloc)(size_t count, size_t size);
    void*   (*_memset)(void *str, int to_swap, unsigned int len);
    char*   (*_duplicate)(const char *str);
    void*	(*_mem_search)(const void *str, int c, size_t n);
    int	    (*_mem_compare)(const void *s1, const void *s2, size_t n);
    void*   (*_mem_copy)(void *dst, const void *src, size_t n);
    void*   (*_mem_set)(void *str, int to_swap, unsigned int len);
    void*   (*_mem_move)(void *dst, const void *src, size_t len);
    void	(*_putstring_n_fd)(char *s, int fd);
    char**  (*_split)(char const *str, char c);
    char*	(*_mapi)(char const *s, char (*f)(unsigned int, char));
    void	(*_iteri)(char *s, void (*f)(unsigned int, char*));
    char*	(*_trim)(char const *s1, char const *set);



} t_string;

t_string *string();

char*   _append(char const *s1, char const *s2);
char*   _strnstr(const char *str, const char *to_find, unsigned int len);
char*   _rear_search(const char *str, char c);
char*   _substr(const char *s, unsigned int start, unsigned int len);
int		_to_lower(int letter);
int		_to_upper(int letter);
// From alpha to integer
int		_atoi(const char *str);
int 	_length(const char *str);
int	    _compare_n(const char *s1, const char *s2, unsigned int n);
char*	_search(const char *str, char c);
int	    _copyl(char *dst, const char *src, int dstsize);
int	    _concatenatel(char *dst, const char *src, int dstsize);
void	_putchar_fd(char c, int fd);
void	_putstring_fd(char *s, int fd);
void	_putstring_n_fd(char *s, int fd);
void	_putnumber_fd(int n, int fd);
int	    _is_alpha(int c);
int	    _is_ascii(int c);
int	    _is_digit(int c);
int	    _is_printable(int c);
int	    _is_alnum(int c);
char*   _itoa(int n);
void	_bzero(void *str, unsigned int n);
void*   _calloc(size_t count, size_t size);
void*   _memset(void *str, int to_swap, unsigned int len);
char*   _duplicate(const char *str);
void*	_mem_search(const void *str, int c, size_t n);
int	    _mem_compare(const void *s1, const void *s2, size_t n);
void*   _mem_copy(void *dst, const void *src, size_t n);
void*   _mem_set(void *str, int to_swap, unsigned int len);
void*   _mem_move(void *dst, const void *src, size_t len);
char**  _split(char const *s, char c);
char*	_mapi(char const *s, char (*f)(unsigned int, char));
void	_iteri(char *s, void (*f)(unsigned int, char*));
char*	_trim(char const *s1, char const *set);


#endif
