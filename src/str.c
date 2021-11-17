/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:04:08 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:04:17 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

void	putstr(char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	write(STDOUT_FILENO, str, l * sizeof(char));
}
