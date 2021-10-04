/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nerror.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/08 11:26:12 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/04 15:05:32 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nerror.h"

static char	*err_get_msg(t_error err)
{
	static char	*err_list[ERR_DEFAULT + 1] =
	{
		[ERR_MALLOC] = "Something went wrong while allocating memory.\n",
		[ERR_DEFAULT] = "UNKNOWN ERROR\n"
	};

	if (err > ERR_DEFAULT)
		err = ERR_DEFAULT;
	return (err_list[err]);
}

static void	_puterr(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(STDERR_FILENO, str, len * sizeof(char));
}

void	error(t_error err)
{
	char	*err_msg;

	if (SPECIFIC_ERROR)
	{
		err_msg = err_get_msg(err);
		_puterr("Error\n- ");
		_puterr(err_msg);
	}
	else
		_puterr("Error\n");
	exit(1);
}
