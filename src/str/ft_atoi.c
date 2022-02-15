/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:12 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 12:35:42 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int	sign;
	int	n;

	while (_isspace(*str))
		str++;
	sign = (*str == '-');
	str += (*str == '+' || *str == '-');
	n = 0;
	while (_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	if (sign)
		return (-n);
	return (n);
}
