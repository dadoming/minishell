/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:08:34 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:08:58 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

void	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
		printf("%s\n", buffer);
	else
		print_normal_error("pwd");
	free(buffer);
	g_exit_status = 0;
}
