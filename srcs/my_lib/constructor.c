/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:50:39 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:26:11 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_lib.h"

t_string	*string(void)
{
	static t_string	s = {_atoi, _length, _rear_search, _strnstr,
		_substr, _to_lower, _to_upper, _compare_n, _compare, _append,
		_search, _copyl, _concatenatel, _putchar_fd, _putstring_fd,
		_putnumber_fd, _itoa, _bzero, _calloc, _mem_set, _duplicate,
		_mem_search, _mem_compare, _mem_copy, _mem_move,
		_putstring_n_fd, _split, _mapi, _iteri, _trim, _arg_count,
		_length_until_c, _copy_until, _array_length, _same_word, _copy,
		_join};

	return (&s);
}

t_check	*check(void)
{
	static t_check	c = {_is_alpha, _is_ascii, _is_digit, _is_printable,
		_is_alnum, _is_space, _is_directory, _is_meta_char};

	return (&c);
}

t_listfunc	*list(void)
{
	static t_listfunc	l = {_new_node, _size, _last, _add_front,
		_add_back, _iterator, _del_node, _clear_list, _del_last_node};

	return (&l);
}
