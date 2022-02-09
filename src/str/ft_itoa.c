/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:29:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

static int	_length(int n)
{
	int	len;

	len = 0;
	if (n == 0 || n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	_set_digits(char *str, int n)
{
	if (n == 0)
		*str = '0';
	while (n != 0)
	{
		*str = n % 10 + '0';
		n = n / 10;
		str--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = _length(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	_set_digits(str + len - 1, n);
	return (str);
}
