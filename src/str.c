/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:04:08 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:44:10 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	putstr(const char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	write(STDOUT_FILENO, str, l * sizeof(char));
}
